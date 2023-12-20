#ifndef NVIDIAIMAGESCALING_H
#define NVIDIAIMAGESCALING_H

#include <QObject>

#include <d3d11.h>
#include <filesystem>
#include <iostream>
#include <tchar.h>
#include <wincodec.h>



#include "BilinearUpscale.h"
#include "DeviceResources.h"
#include <windows.h>
#include "../common/Image.h"
#include <QDebug>
#include "NVScaler.h"
#include "NVSharpen.h"
#include <QImageReader>

using namespace img;




class NVIDIAImageScaling : public QObject
{
    Q_OBJECT
public:
    explicit NVIDIAImageScaling(QObject* parent = nullptr);



    const QString& srcPath() const;
    void setSrcPath(const QString& newSrcPath);

    const QString& destPath() const;
    void setDestPath(const QString& newDestPath);
    void convert();


    HWND hwnd() const;
    void setHwnd(HWND newHwnd);
    void render();

    float scale() const;
    void setScale(float newScale);

    float sharp() const;
    void setSharp(float newSharp);

signals:
private:
    QString m_srcPath;
    QString m_destPath;
    HWND m_hwnd;
    DeviceResources m_deviceResources;
    float m_scale;
    float m_sharp;
    ComPtr<ID3D11Query>                 m_timeStampDis;
    ComPtr<ID3D11Query>                 m_timeStampStart;
    ComPtr<ID3D11Query>                 m_timeStampEnd;
    ComPtr<ID3D11Texture2D>             m_input;
    ComPtr<ID3D11Texture2D>             m_output;
    ComPtr<ID3D11ShaderResourceView>    m_inputSRV;
    ComPtr<ID3D11UnorderedAccessView>   m_outputUAV;
    uint32_t rowPitch;
    uint32_t m_inputWidth;
    uint32_t m_inputHeight;
    uint32_t m_outputWidth;
    uint32_t m_outputHeight;
    bool m_enableNVScaler;




};

#endif // NVIDIAIMAGESCALING_H
