#pragma once

#include "DirectXIncLib.h"

//シェーダー用のコンスタントバッファーのアプリ側構造体 シェーダー内のコンスタントバッファーと一致している必要あり
struct SimpleShaderConstantBuffer0 {
    D3DXMATRIX mW;//ワールド行列
    D3DXMATRIX mWVP;//ワールドから射影までの変換行列
    D3DXVECTOR4 mLightDir;//ライト方向
    D3DXVECTOR4 mEye;//カメラ位置	
};

struct SimpleShaderConstantBuffer1 {
    D3DXVECTOR4 mAmbient;//アンビエント光
    D3DXVECTOR4 mDiffuse;//ディフューズ色
    D3DXVECTOR4 mSpecular;//鏡面反射
    D3DXVECTOR4 mTexture;//テクスチャーが貼られているメッシュかどうかのフラグ
};

struct D3DInit {
    HWND mHwnd;
};

class Direct3D11 {
public:
    Direct3D11();
    ~Direct3D11();
    HRESULT init(D3DInit*);
    void clear();
    HRESULT present();

    static ID3D11Device* mDevice;
    static ID3D11DeviceContext* mDeviceContext;
    static ID3D11RasterizerState* mRasterizerState; //前面用
    static ID3D11RasterizerState* mRasterizerStateBack; //背面用

private:
    HWND mHwnd;
    IDXGISwapChain* mSwapChain;
    ID3D11RenderTargetView* mRenderTargetView;
    ID3D11DepthStencilView* mDepthStencilView;
    ID3D11Texture2D* mDepthStencil;
    ID3D11DepthStencilState* mDepthStencilState;
};

