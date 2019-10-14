#pragma once

#include "../System/DirectXIncLib.h"
#include "../Utility/Collision.h"
#include "../Utility/Math.h"
#include <memory>
#include <stdio.h>
#include <string>
#include <vector>

//Simpleシェーダー用のコンスタントバッファーのアプリ側構造体 もちろんシェーダー内のコンスタントバッファーと一致している必要あり
struct SIMPLESHADER_CONSTANT_BUFFER0 {
    Matrix4 mW;//ワールド行列
    Matrix4 mWVP;//ワールドから射影までの変換行列
    Vector4 vLightDir;//ライト方向
    Vector4 vEye;//カメラ位置
};

struct SIMPLESHADER_CONSTANT_BUFFER1 {
    D3DXVECTOR4 vAmbient;//アンビエント光
    D3DXVECTOR4 vDiffuse;//ディフューズ色
    D3DXVECTOR4 vSpecular;//鏡面反射
    D3DXVECTOR4 vTexture;//テクスチャーが貼られているメッシュかどうかのフラグ
};

//頂点の構造体
struct MeshVertex {
    D3DXVECTOR3 mPos;
    D3DXVECTOR3 mNorm;
    D3DXVECTOR2 mTex;
};

//オリジナル　マテリアル構造体
struct Material {
    CHAR szName[110];
    D3DXVECTOR4 Ka;//アンビエント
    D3DXVECTOR4 Kd;//ディフューズ
    D3DXVECTOR4 Ks;//スペキュラー
    CHAR szTextureName[110];//テクスチャーファイル名
    ID3D11ShaderResourceView* pTexture;
    DWORD dwNumFace;//そのマテリアルであるポリゴン数
    Material() {
        ZeroMemory(this, sizeof(Material));
    }
    ~Material() {
        SAFE_RELEASE(pTexture);
    }
};

class Shader;

class Mesh {
public:
    Mesh();
    ~Mesh();
    HRESULT init(const std::string& fileName);
    void draw(Matrix4 world, float alpha) const;
    void createSphere(Sphere* sphere) const;

    DWORD getNumMaterial() const {
        return mNumMaterial;
    }
    DWORD* getNumFace() const {
        return mNumFaceInMaterial;
    }
    MeshVertex* getVertexBuffer() const {
        return mMyVertexBuffer;
    }
    int** getVertexIndex() const {
        return mVertexIndex;
    }

private:
    HRESULT LoadMaterialFromFile(const std::string& fileName, Material** ppMaterial);
    HRESULT LoadStaticMesh(const std::string& fileName);
    void RendererMesh(Matrix4 world, float alpha) const;

    ID3D11Device* mDevice;
    ID3D11DeviceContext* mDeviceContext;
    ID3D11RasterizerState* mRasterizerState;
    ID3D11RasterizerState* mRasterizerStateBack;

    DWORD mNumVert;
    DWORD mNumFace;
    ID3D11Buffer* mVertexBuffer;
    ID3D11Buffer** mIndexBuffer;
    DWORD mNumMaterial;
    Material* mMaterial;
    ID3D11SamplerState* mSampleLinear;
    ID3D11ShaderResourceView* mTexture;

    MeshVertex* mMyVertexBuffer;
    int** mVertexIndex;
    DWORD* mNumFaceInMaterial;
    D3DXVECTOR3* mCoord;

    std::shared_ptr<Shader> mShader;
};