# RE-RE
Reversing reverse-engineered softwares!?

## Usage

* Install https://www.elcomsoft.com/download/epr_agent_setup_en.msi (3.01.853)
  - This is just to make espr_office.dll file happy!
  - We don't actually use it!

## Toolchain Setup

```
$ sudo dnf install mingw32-openssl mingw32-openssl-static \
	mingw32-gcc mingw32-gcc-c++ binutils \
	mingw32-winpthreads-static -y
```

## Notes

```
$ target=$HOME/.wine/drive_c/Program\ Files\ \(x86\)/Elcomsoft/Common\ Files/
$ mkdir -p "$target"
$ cp lib/elcom_xml.dll "$target"

// sub_100142C0 is iWork09_parser ;)
int __cdecl iWork09_parser(LPCWSTR lpFileName, int a2)
{
  HANDLE v2; // eax@1
  void *v3; // esi@1
  int result; // eax@2
  DWORD v5; // eax@3
  DWORD v6; // ebp@3
  HLOCAL v7; // ebx@5
  int v8; // eax@11
  bool v9; // zf@11
  int v10; // eax@18
  unsigned __int16 v11; // dx@21
  int v12; // eax@24
  void *v13; // [sp-Ch] [bp-2Ch]@19
  int v14; // [sp+8h] [bp-18h]@0
  DWORD NumberOfBytesRead; // [sp+Ch] [bp-14h]@7
  char v16; // [sp+18h] [bp-8h]@24

  v2 = CreateFileW(lpFileName, 0x80000000, 3u, 0, 3u, 0, 0);
  v3 = v2;
  if ( v2 == (HANDLE)-1 )
    return 1;
  v5 = GetFileSize(v2, 0);
  v6 = v5;
  if ( v5 && v5 != -1 )
  {
    v7 = LocalAlloc(0, v5);
    if ( !v7 )
    {
      CloseHandle(v3);
      return 4;
    }
    if ( ReadFile(v3, v7, v6, &NumberOfBytesRead, 0) && NumberOfBytesRead == v6 )
    {
      CloseHandle(v3);
      if ( *(_DWORD *)v7 != 0x4034B50 )         // http://result42.com/projects/ZipFileLayout
      {
        LocalFree(v7);
        return 3;
      }
      v8 = (int)((char *)v7 + v6 - 4);
      v9 = v8 == (_DWORD)v7;
      if ( v8 > (unsigned int)v7 )
      {
        while ( *(_DWORD *)v8 != 0x6054B50 )    // ZIP constant!
        {
          --v8;
          if ( v8 <= (unsigned int)v7 )
            goto LABEL_16;
        }
        v14 = v8;
LABEL_16:
        v9 = v8 == (_DWORD)v7;
      }
      if ( v9 || (v10 = (int)((char *)v7 + *(_DWORD *)(v14 + 16)), *(_DWORD *)v10 != 0x2014B50) )// another zip constant!
      {
        v13 = v7;
LABEL_20:
        LocalFree(v13);
        return 6;
      }
      v11 = *(_WORD *)(v10 + 30);
      v13 = v7;
      if ( v11 )
      {
        if ( v11 < 0x6Cu )
          goto LABEL_20;
        v12 = *(_WORD *)(v10 + 28) + v10;
        v16 = 0;
        *(_DWORD *)a2 = *(_DWORD *)(v12 + 54);
        *(_DWORD *)(a2 + 4) = *(_DWORD *)(v12 + 58);
        *(_DWORD *)(a2 + 8) = 0x656D6F73;
        *(_DWORD *)(a2 + 12) = 0x746C6153;
        *(_DWORD *)(a2 + 24) = 8;
        qmemcpy((void *)(a2 + 28), (const void *)(v12 + 62), 80u);// 80 bytes of what?
        LocalFree(v7);
        result = 0;
      }
      else
      {
        LocalFree(v7);
        result = 11;
      }
    }
    else
    {
      LocalFree(v7);
      CloseHandle(v3);
      result = 2;
    }
  }
  else
  {
    CloseHandle(v3);
    result = 1;
  }
  return result;
}
```

## References

* https://www.winehq.org/docs/winedev-guide/wine-debugger
