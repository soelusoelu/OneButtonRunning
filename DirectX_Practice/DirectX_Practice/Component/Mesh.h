#pragma once

#include "../DirectXIncLib.h"
#include "../Utility/Collision.h"
#include <memory>
#include <stdio.h>
#include <string>

#define SAFE_RELEASE(x) if(x){x->Release(); x=0;}
#define SAFE_DELETE(x) if(x){delete x; x=0;}
#define SAFE_DELETE_ARRAY(x) if(x){delete[] x; x=0;}

//���_�̍\����
struct MY_VERTEX {
    D3DXVECTOR3 vPos;
    D3DXVECTOR3 vNorm;
    D3DXVECTOR2 vTex;
};
//Simple�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\���� �������V�F�[�_�[���̃R���X�^���g�o�b�t�@�[�ƈ�v���Ă���K�v����
struct SIMPLESHADER_CONSTANT_BUFFER0 {
    D3DXMATRIX mW;//���[���h�s��
    D3DXMATRIX mWVP;//���[���h����ˉe�܂ł̕ϊ��s��
    D3DXVECTOR4 vLightDir;//���C�g����
    D3DXVECTOR4 vEye;//�J�����ʒu
};

struct SIMPLESHADER_CONSTANT_BUFFER1 {
    D3DXVECTOR4 vAmbient;//�A���r�G���g��
    D3DXVECTOR4 vDiffuse;//�f�B�t���[�Y�F
    D3DXVECTOR4 vSpecular;//���ʔ���
    D3DXVECTOR4 vTexture;//�e�N�X�`���[���\���Ă��郁�b�V�����ǂ����̃t���O
};
//�I���W�i���@�}�e���A���\����
struct MY_MATERIAL {
    CHAR szName[110];
    D3DXVECTOR4 Ka;//�A���r�G���g
    D3DXVECTOR4 Kd;//�f�B�t���[�Y
    D3DXVECTOR4 Ks;//�X�y�L�����[
    CHAR szTextureName[110];//�e�N�X�`���[�t�@�C����
    ID3D11ShaderResourceView* pTexture;
    DWORD dwNumFace;//���̃}�e���A���ł���|���S����
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
    ID3D11BlendState* mBlendState; //�A���t�@�u�����f�B���O

    MY_VERTEX* pvVertexBuffer;
    int** ppiVertexIndex;
    DWORD* dwNumFaceInMaterial;

    D3DXVECTOR3* mCoord;

};