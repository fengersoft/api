#include "nvidiaimagescaling.h"

NVIDIAImageScaling::NVIDIAImageScaling(QObject* parent)
    : QObject{parent}
{
    m_scale = 100;
    m_sharp = 50;
    m_inputWidth = 1920;
    m_inputHeight = 1080;
    m_outputWidth = 1920;
    m_outputHeight = 1080;
    m_enableNVScaler = true;


}

const QString& NVIDIAImageScaling::srcPath() const
{
    return m_srcPath;
}

void NVIDIAImageScaling::setSrcPath(const QString& newSrcPath)
{
    m_srcPath = newSrcPath;
    QImageReader reader(m_srcPath);
    QSize sz = reader.size();
    m_inputWidth = sz.width();
    m_inputHeight = sz.height();
}

const QString& NVIDIAImageScaling::destPath() const
{
    return m_destPath;
}

void NVIDIAImageScaling::setDestPath(const QString& newDestPath)
{
    m_destPath = newDestPath;
}

void NVIDIAImageScaling::convert()
{


    std::vector<uint8_t> image;


    if (m_scale == 100)
    {
        m_outputWidth = m_inputWidth;
        m_outputHeight = m_inputHeight;
    }
    else
    {
        m_outputWidth = uint32_t(std::ceil(m_inputWidth * 100.f / m_scale));
        m_outputHeight = uint32_t(std::ceil(m_inputHeight * 100.f / m_scale));
    }

    img::load(m_srcPath.toStdString(), image, m_inputWidth, m_inputHeight, rowPitch, img::Fmt::R8G8B8A8);
    m_deviceResources.createTexture2D(m_inputWidth, m_inputHeight, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_USAGE_DEFAULT, image.data(), rowPitch, rowPitch * m_inputHeight, &m_input);
    m_deviceResources.createSRV(m_input.Get(), DXGI_FORMAT_R8G8B8A8_UNORM, &m_inputSRV);
    m_deviceResources.createTexture2D(m_outputWidth, m_outputHeight, DXGI_FORMAT_R8G8B8A8_UNORM,
                                      D3D11_USAGE_DEFAULT, nullptr, 0, 0, &m_output);
    m_deviceResources.createUAV(m_output.Get(), DXGI_FORMAT_R8G8B8A8_UNORM, &m_outputUAV);

    render();

    D3D11_TEXTURE2D_DESC desc;
    m_output->GetDesc(&desc);
    img::Fmt format = img::Fmt::R8G8B8A8;

    switch (desc.Format)
    {
    case DXGI_FORMAT_R8G8B8A8_UNORM:
        format = img::Fmt::R8G8B8A8;
        break;
    case DXGI_FORMAT_R32G32B32A32_FLOAT:
        format = img::Fmt::R32G32B32A32;
        break;
    case DXGI_FORMAT_R16G16B16A16_FLOAT:
        format = img::Fmt::R16G16B16A16;
        break;
    }
    std::vector<uint8_t> data;
    uint32_t width, height = 0;
    constexpr uint32_t channels = 4;

    m_deviceResources.getTextureData(m_output.Get(), data, width, height, rowPitch);
    qDebug() << width << height << data.data();
    img::save(m_destPath.toStdString(), data.data(), width, height, channels, rowPitch, format);
    qDebug() << m_destPath << height;


}

HWND NVIDIAImageScaling::hwnd() const
{
    return m_hwnd;
}

void NVIDIAImageScaling::setHwnd(HWND newHwnd)
{
    m_hwnd = newHwnd;
    m_deviceResources.create(m_hwnd);
}

void NVIDIAImageScaling::render()
{
    std::vector<std::string> shaderPaths{ "NIS/"};
    NVSharpen                           m_NVSharpen(m_deviceResources, shaderPaths);
    NVScaler                            m_NVScaler(m_deviceResources, shaderPaths);
    BilinearUpscale m_upscale(m_deviceResources);

    m_upscale.update(m_inputWidth, m_inputHeight, m_outputWidth, m_outputHeight);
    m_NVScaler.update(m_sharp / 100.f, m_inputWidth, m_inputHeight, m_outputWidth, m_outputHeight);
    m_NVSharpen.update(m_sharp / 100.f, m_inputWidth, m_inputHeight);



    auto context = m_deviceResources.context();
    D3D11_QUERY_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_QUERY_DESC));
    desc.Query = D3D11_QUERY_TIMESTAMP_DISJOINT;
    m_deviceResources.device()->CreateQuery(&desc, &m_timeStampDis);
    desc.Query = D3D11_QUERY_TIMESTAMP;
    m_deviceResources.device()->CreateQuery(&desc, &m_timeStampStart);
    m_deviceResources.device()->CreateQuery(&desc, &m_timeStampEnd);
    context->Begin(m_timeStampDis.Get());
    context->End(m_timeStampStart.Get());

    if (!m_enableNVScaler)
    {
        if (m_scale == 100)
        {
            context->CopyResource(m_output.Get(), m_input.Get());
        }
        else
        {
            m_upscale.dispatch(m_inputSRV.GetAddressOf(), m_outputUAV.GetAddressOf());
        }
    }
    else
    {
        if (m_scale == 100)
        {
            m_NVSharpen.dispatch(m_inputSRV.GetAddressOf(), m_outputUAV.GetAddressOf());
        }
        else
        {
            m_NVScaler.dispatch(m_inputSRV.GetAddressOf(), m_outputUAV.GetAddressOf());
        }
    }



    context->End(m_timeStampEnd.Get());
    context->End(m_timeStampDis.Get());
    D3D11_QUERY_DATA_TIMESTAMP_DISJOINT disData;
    while (context->GetData(m_timeStampDis.Get(), &disData, sizeof(D3D11_QUERY_DATA_TIMESTAMP_DISJOINT), 0) != S_OK);
    UINT64 startime;
    UINT64 endtime;
    while (context->GetData(m_timeStampStart.Get(), &startime, sizeof(UINT64), 0) != S_OK);
    while (context->GetData(m_timeStampEnd.Get(), &endtime, sizeof(UINT64), 0) != S_OK);

    D3D11_BOX sourceRegion;
    sourceRegion.left = 0;
    sourceRegion.right = m_deviceResources.width();
    sourceRegion.top = 0;
    sourceRegion.bottom = m_deviceResources.height();
    sourceRegion.front = 0;
    sourceRegion.back = 1;
    context->CopySubresourceRegion(m_deviceResources.renderTarget(), 0, 0, 0, 0, m_output.Get(), 0, &sourceRegion);
    context->OMSetRenderTargets(1, m_deviceResources.targetViewAddress(), nullptr);

}

float NVIDIAImageScaling::scale() const
{
    return m_scale;
}

void NVIDIAImageScaling::setScale(float newScale)
{
    m_scale = newScale;
}

float NVIDIAImageScaling::sharp() const
{
    return m_sharp;
}

void NVIDIAImageScaling::setSharp(float newSharp)
{
    m_sharp = newSharp;
}




