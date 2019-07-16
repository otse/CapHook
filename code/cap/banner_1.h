#pragma once

#include <d3d11.h>

#include <map>

namespace cap
{
	extern bool ChrisOrSebastian;

	struct Banner
	{
		ID3D11Texture2D *texture;
		ID3D11ShaderResourceView* view;
	};
	extern std::map<const std::wstring, Banner> banners_;

	void CAPUPLOADBANNER(const wchar_t *);

	void CAPDRAWBANNER();
	
	void CAPSTOREVARS(
		IDXGISwapChain *,
		ID3D11Device *,
		ID3D11DeviceContext *,
		ID3D11RenderTargetView *);

	struct CAPVARS
	{
		IDXGISwapChain *swapchain;
		ID3D11Device *device;
		ID3D11DeviceContext *context;
		ID3D11RenderTargetView *rtv;
	};
}