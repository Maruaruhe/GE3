#include "DirectXCommon.h"

#include <cassert>
#include <vector>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

using namespace Microsoft::WRL;

void DirectXCommon::Initialize(WindowsAPI* winAPI) {
	assert(winAPI);
	this->winAPI_ = winAPI;
}

void DirectXCommon::Update() {

}

void DirectXCommon::InitializeAdapter() {

}

void DirectXCommon::InitializeDevice() {
	HRESULT result;
#ifdef _DEBUG
	ComPtr<ID3D12Debug> debugController;
	//デバッグレイヤーを有効化する
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
		debugController->EnableDebugLayer();
		//さらにGPU側でもチェックを行うようにする
		//debugController->SetEnableGPUBasedValidation(TRUE);
	}
#endif

	device_ = nullptr;

	//DXGIファクトリーの生成
	result = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory_));
	assert(SUCCEEDED(result));

	//アダプターの列挙
	std::vector<IDXGIAdapter4*> adapters;
	//ここに特定の名前を持つアダプターオブジェクトが入る
	IDXGIAdapter4* tmpAdapter = nullptr;
	//パフォーマンスが高いものから順に、全てのアダプターを列挙する
	for (UINT i = 0; dxgiFactory_->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND; i++) {
		//動的配列に追加する
		adapters.push_back(tmpAdapter);
	}
	//妥当なアダプタを選別する
	for (size_t i = 0; i < adapters.size(); i++) {
		DXGI_ADAPTER_DESC3 adapterDesc;
		//アダプタの情報をを取得する
		adapters[i]->GetDesc3(&adapterDesc);
		//ソフトウェアデバイスを回避
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			//デバイスを採用してループを抜ける
			tmpAdapter = adapters[i];
			break;
		}
	}
	
	//デバイスの生成

	//対応レベルの配列
	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	D3D_FEATURE_LEVEL featureLevel;

	for (size_t i = 0; i < _countof(levels); i++) {
		//採用したアダプタでデバイスを生成
		result = D3D12CreateDevice(tmpAdapter, levels[i], IID_PPV_ARGS(&device_));
		if (result == S_OK) {
			//デバイス生成できた時点でループを抜ける
			featureLevel = levels[i];
			break;
		}
	}
}

void DirectXCommon::InitializeCommand() {
	HRESULT result;
	//コマンドアロケータ生成
	result = device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
	assert(SUCCEEDED(result));
	//コマンドリスト生成

	//コマンドキュー生成
}

void DirectXCommon::InitializeSwapChain() {

}

void DirectXCommon::InitializeRenderTargetView() {

}

void DirectXCommon::InitializeDepthBuffer() {

}

void DirectXCommon::InitializeFence() {

}
