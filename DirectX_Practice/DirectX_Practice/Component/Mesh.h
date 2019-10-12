#pragma once

#include "../DirectXIncLib.h"
#include "../Utility/Collision.h"
#include <memory>
#include <stdio.h>
#include <string>

class Shader;

//頂点の構造体
struct MY_VERTEX {
    D3DXVECTOR3 vPos;
    D3DXVECTOR3 vNorm;
    D3DXVECTOR2 vTex;
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
    HRESULT init(const std::string& fileName);
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
    DWORD m_dwNumMaterial;
    MY_MATERIAL* m_pMaterial;
    ID3D11SamplerState* m_pSampleLinear;
    ID3D11ShaderResourceView* m_pTexture;

    MY_VERTEX* pvVertexBuffer;
    int** ppiVertexIndex;
    DWORD* dwNumFaceInMaterial;
    D3DXVECTOR3* mCoord;

    std::shared_ptr<Shader> mShader;
};