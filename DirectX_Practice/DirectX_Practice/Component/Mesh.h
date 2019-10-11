#pragma once

#include "../DirectXIncLib.h"
#include "../Utility/Collision.h"
#include <memory>
#include <stdio.h>
#include <string>

#define SAFE_RELEASE(x) if(x){x->Release(); x=0;}
#define SAFE_DELETE(x) if(x){delete x; x=0;}
#define SAFE_DELETE_ARRAY(x) if(x){delete[] x; x=0;}

//頂点の構造体
struct MY_VERTEX {
    D3DXVECTOR3 vPos;
    D3DXVECTOR3 vNorm;
    D3DXVECTOR2 vTex;
};
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
//オリジナル　マテリアル構造体
struct MY_MATERIAL {
    CHAR szName[110];
    D3DXVECTOR4 Ka;//アンビエント
    D3DXVECTOR4 Kd;//ディフューズ
    D3DXVECTOR4 Ks;//スペキュラー
    CHAR szTextureName[110];//テクスチャーファイル名
    ID3D11ShaderResourceView* pTexture;
    DWORD dwNumFace;//そのマテリアルであるポリゴン数
    MY_MATERIAL() {
        ZeroMemory(this, sizeof(MY_MATERIAL));
    }
    ~MY_MATERIAL() {
        SAFE_RELEASE(pTexture);
    }
};

class Mesh {
public:
    Mesh();
    ~Mesh();
    HRESULT Init(const std::string& fileName);
    void draw(D3DXMATRIX world, float alpha) const;
    void createSphere(Sphere* sphere) const;

    DWORD getNumMaterial() const {
        return m_dwNumMaterial;
    }
    DWORD* getNumFace() const {
        return dwNumFaceInMaterial;
    }
    MY_VERTEX* getVertexBuffer() const {
        return pvVertexBuffer;
    }
    int** getVertexIndex() const {
        return ppiVertexIndex;
    }

private:
    HRESULT InitShader();
    HRESULT LoadMaterialFromFile(const std::string& fileName, MY_MATERIAL** ppMaterial);
    HRESULT LoadStaticMesh(const std::string& fileName);
    void RendererMesh(D3DXMATRIX world, float alpha) const;

    ID3D11Device* m_pDevice;
    ID3D11DeviceContext* m_pDeviceContext;
    ID3D11RasterizerState* mRasterizerState;
    ID3D11RasterizerState* mRasterizerStateBack;

    DWORD m_dwNumVert;
    DWORD m_dwNumFace;
    ID3D11Buffer* m_pVertexBuffer;
    ID3D11Buffer** m_ppIndexBuffer;
    ID3D11InputLayout* m_pVertexLayout;
    ID3D11VertexShader* m_pVertexShader;
    ID3D11PixelShader* m_pPixelShader;
    ID3D11Buffer* m_pConstantBuffer0;
    ID3D11Buffer* m_pConstantBuffer1;
    DWORD m_dwNumMaterial;
    MY_MATERIAL* m_pMaterial;
    ID3D11SamplerState* m_pSampleLinear;
    ID3D11ShaderResourceView* m_pTexture;
    ID3D11BlendState* mBlendState; //アルファブレンディング

    MY_VERTEX* pvVertexBuffer;
    int** ppiVertexIndex;
    DWORD* dwNumFaceInMaterial;

    D3DXVECTOR3* mCoord;

};