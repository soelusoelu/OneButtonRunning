#pragma once

#include "../DirectXIncLib.h"
#include <string>

//Simpleシェーダー用のコンスタントバッファーのアプリ側構造体 もちろんシェーダー内のコンスタントバッファーと一致している必要あり
struct SIMPLESHADER_CONSTANT_BUFFER0 {
    D3DXMATRIX mW;//ワールド行列
    D3DXMATRIX mWVP;//ワールドから射影までの変換行列
    D3DXVECTOR4 vLightDir;//ライト方向
    D3DXVECTOR4 vEye;//カメラ位置
};

struct SIMPLESHADER_CONSTANT_BUFFER1 {
    D3DXVECTOR4 vAmbient;//アンビエント光
    D3DXVECTOR4 vDiffuse;//ディフューズ色
    D3DXVECTOR4 vSpecular;//鏡面反射
    D3DXVECTOR4 vTexture;//テクスチャーが貼られているメッシュかどうかのフラグ
};

class Shader {
public:
    Shader();
    ~Shader();
    void init(const std::string& fileName);

    ID3D11VertexShader* getVertexShader() const {
        return mVertexShader;
    }
    ID3D11InputLayout* getVertexLayout() const {
        return mVertexLayout;
    }
    ID3D11PixelShader* getPixelShader() const {
        return mPixelShader;
    }
    ID3D11Buffer* mConstantBuffer0;
    ID3D11Buffer* mConstantBuffer1;

private:
    HRESULT initShader(const std::string& fileName);

    ID3D11Device* mDevice;
    ID3D11DeviceContext* mDeviceContext;

    ID3D11VertexShader* mVertexShader;
    ID3D11InputLayout* mVertexLayout;
    ID3D11PixelShader* mPixelShader;
    ID3D11BlendState* mBlendState; //アルファブレンディング
};

