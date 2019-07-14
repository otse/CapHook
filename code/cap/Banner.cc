#pragma once

#include "Console.h"
#include "Banner.h"

#include <Windows.h>
#include <d3d11.h>
#include <iostream>
#include <string>

#include <imgui.h>

#include <comdef.h>

#include <Utility/PathUtils.h>

namespace cap
{
bool ChrisOrSebastian = false;

ID3D11ShaderResourceView *TextureView_ = NULL;

ID3D11Texture2D *pTexture = NULL;
//ID3D11Texture2D *pTexture1 = NULL;

CAPVARS vars;

void CAPSTOREVARS(
	IDXGISwapChain *swapchain,
	ID3D11Device *device,
	ID3D11DeviceContext *context,
	ID3D11RenderTargetView *rtv)
{
	std::puts("Stored id3d for cap");

	vars.swapchain = swapchain;
	vars.device = device;
	vars.context = context;
	vars.rtv = rtv;
}

void CAPDRAWBANNER()
{
	static bool banner = true;

	auto flags = ImGuiWindowFlags_NoMove |
				 ImGuiWindowFlags_NoTitleBar |
				 ImGuiWindowFlags_AlwaysAutoResize |
				 ImGuiWindowFlags_NoSavedSettings |
				 ImGuiWindowFlags_NoFocusOnAppearing |
				 ImGuiWindowFlags_NoNav;

	ImGuiIO &io = ImGui::GetIO();

	//ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, ImVec2(0, 0));

	ImGui::SetNextWindowBgAlpha(0.0f);

	ImVec2 window_pos = ImVec2(io.DisplaySize.x - 50, 50);
	ImVec2 window_pos_pivot = ImVec2(1.0f, 0.0f);
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	//ImGui::SetNextWindowSize(ImVec2(700, 150));

	ImGui::Begin("Banner", &banner, flags);
	ImGui::Image((void *)TextureView_, ImVec2(900, 500));
	ImGui::End();

	//ImGui::PopStyleVar(1);
}

void CAPUPLOADBANNER()
{
	const wchar_t *swap = L"shieldmod\\chris or seb";

	auto chris_or_seb = Utility::MakeAbsolutePathW(swap).c_str();
	
	if (INVALID_FILE_ATTRIBUTES != GetFileAttributesW(chris_or_seb))
	{
		ChrisOrSebastian = true;
		DeleteFileW(chris_or_seb);
	}
	else
	{
		ChrisOrSebastian = false;
		CreateFileW(chris_or_seb, GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	int width = 900;
	int height = 500;
	//int width = 512;
	//int height = 512;

	auto path = Utility::MakeAbsolutePathW(L"shieldmod\\");

	auto pink = ChrisOrSebastian ? L"pink captain america" : L"pink winter soldier";
	
	auto banner = (path + pink).c_str();

	// F
	FILE *fh = nullptr;
	_wfopen_s(&fh, banner, L"rb");

	fseek(fh, 0, SEEK_END);

	auto length = ftell(fh);

	fseek(fh, 0, SEEK_SET);

	unsigned char *data = new unsigned char[length];
	data[length] = 0;
	fread(data, 1, length, fh);
	fclose(fh);
	// F

	unsigned char *pixels = data;

	int h = 0;
	for (; h < height; h++)
	{
		int w = 0;
		for (; w < width; w++)
		{
			//pixels += data.;
		}
	}

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = pixels;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;

	HRESULT hr = vars.device->CreateTexture2D(&desc, &subResource, &pTexture);

	if (FAILED(hr))
	{

		std::cout << "capuploadbanner texture2d hresult " << std::hex << hr << std::endl;

		return;
	}

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;

	hr = vars.device->CreateShaderResourceView(pTexture, &srvDesc, &TextureView_);

	if (FAILED(hr))
	{

		std::cout << "capuploadbanner textureview hresult " << std::hex << hr << std::endl;

		return;
	}
}

} // namespace cap