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
	result = device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator_));
	assert(SUCCEEDED(result));
	//コマンドリスト生成
	result = device_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator_.Get(), nullptr, IID_PPV_ARGS(&commandList_));
	assert(SUCCEEDED(result));
	//コマンドキュー生成
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	result = device_->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue_));
	assert(SUCCEEDED(result));
}

void DirectXCommon::InitializeSwapChain() {
	HRESULT result;
	//スワップチェーン生成の設定
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	swapChainDesc.Width = 1280;
	swapChainDesc.Height = 720;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	//swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	//スワップチェーン生成
	ComPtr<IDXGISwapChain1> swapChain1;

	result = dxgiFactory_->CreateSwapChainForHwnd(commandQueue_.Get(), winAPI_->GetHwnd(), &swapChainDesc, nullptr, nullptr, (IDXGISwapChain1**)&swapChain1);
	assert(SUCCEEDED(result));
	//IDXGISwapCahin1のオブジェクトをIDXGISwapChain4に変換

}

void DirectXCommon::InitializeRenderTargetView() {
	HRESULT result;

	DXGI_SWAP_CHAIN_DESC swcDesc = {};
	result = swapChain_->GetDesc(&swcDesc);
	assert(SUCCEEDED(result));
	//RTV用デスクリプターヒープ生成
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};

	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.NumDescriptors = swcDesc.BufferCount;

    result = device_->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeap_));
	assert(SUCCEEDED(result));
	//裏表の2つ分
	backBuffers_.resize(swcDesc.BufferCount);
	for (int i = 0; i < backBuffers_.size(); i++) {
		//スワップチェーンからバッファを取得
		
		// デスクリプターヒープのバンドルを取得
		
		// 裏か表でアドレスがずれる

		//レンダーターゲットビューの設定

		//シェーダーの計算結果をSRGBに変換して書き込む
		
		//レンダーターゲットビューの生成

	}
}

void DirectXCommon::InitializeDepthBuffer() {
	//深度バッファリソース生成
	
	// 深度バッファ生成
	
	// DSV用デスクリプターヒープ生成
	
	//深度バッファビュー（DSV）生成

}

void DirectXCommon::InitializeFence() {

}
