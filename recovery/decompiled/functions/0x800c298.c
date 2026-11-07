// rea decompile_all
// name: fw_0800c298
// address: 0x800c298
// body: available
// range: 0x800c298-0x800c691 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_0800c298(void)

{
  undefined2 uVar1;
  uint uVar2;
  uint uVar3;
  undefined1 *puVar4;
  undefined4 in_r3;
  int iVar5;
  bool bVar6;
  
  uVar2 = fw_0800a46c(0xf114);
  uVar3 = 0;
  do {
    if ((1 << (uVar3 & 0xff) & uVar2) == 0) {
      *(undefined1 *)(uVar3 + 0x20000b1e) = 1;
    }
    uVar3 = uVar3 + 1 & 0xffff;
  } while (uVar3 < 0xc);
  uVar2 = fw_08005340(&DAT_0800fc00);
  uVar3 = fw_08005340(&DAT_0800fc5e);
  bVar6 = (uVar3 ^ 0xffff) == uVar2;
  do {
    if (!bVar6) {
      _DAT_20000856 = 0xf0;
      _DAT_20000858 = 0xf0;
      _DAT_2000085c = 10;
      _DAT_2000085e = 10;
      _DAT_2000085a = 10;
      _DAT_20000860 = 200;
      _DAT_20000862 = 400;
      _DAT_20000864 = 600;
      _DAT_20000866 = 0x898;
      _DAT_20000868 = 0x4b;
      _DAT_2000086a = 0x32;
      _DAT_2000086c = 0x19;
      _DAT_2000086e = 1;
      _DAT_20000870 = 1;
      _DAT_20000872 = 0x14;
      _DAT_20000874 = 0x2a30;
      _DAT_20000876 = 0;
      _DAT_200008be = 1;
      _DAT_200008bc = 1;
      _DAT_2000088c = 0;
      _DAT_20000890 = 0;
      _DAT_20000894 = 0;
      _DAT_20000898 = 0;
      _DAT_20000878 = 3;
      _DAT_2000087a = 0x78;
      _DAT_2000087c = 6;
      DAT_200008cb = 7;
      _DAT_2000087e = 0x2d0;
      _DAT_20000880 = 6;
      _DAT_200008c8 = 1;
      _DAT_200008b8 = 0;
      DAT_20000102 = 'P';
      _DAT_2000010c = 0x157c;
      _DAT_20000118 = 0x1ef0;
      fw_0800a4a8(&DAT_0800fc00,0x3ec9,6,0x2d0,in_r3);
      fw_0800a4a8(&DAT_0800fc02,_DAT_20000856);
      fw_0800a4a8(&DAT_0800fc04,_DAT_20000858);
      fw_0800a4a8(&DAT_0800fc06,_DAT_2000085c);
      fw_0800a4a8(&DAT_0800fc08,_DAT_2000085e);
      fw_0800a4a8(&DAT_0800fc0a,_DAT_2000085a);
      uVar2 = 0;
      do {
        iVar5 = uVar2 * 2;
        puVar4 = &DAT_20000854 + iVar5;
        fw_0800a4a8(&DAT_0800fc0c + iVar5,*(undefined2 *)(&DAT_20000860 + iVar5));
        if (uVar2 < 3) {
          fw_0800a4a8(&DAT_0800fc14 + iVar5,*(undefined2 *)(puVar4 + 0x14));
        }
        uVar2 = uVar2 + 1 & 0xffff;
      } while (uVar2 < 4);
      fw_0800a4a8(&DAT_0800fc1a,_DAT_2000086e);
      fw_0800a4a8(&DAT_0800fc1c,_DAT_20000870);
      fw_0800a4a8(&DAT_0800fc1e,_DAT_20000872);
      fw_0800a4a8(&DAT_0800fc20,_DAT_20000874);
      fw_0800a4a8(&DAT_0800fc22,_DAT_20000876);
      fw_0800a4a8(&DAT_0800fc24,_DAT_20000878);
      fw_0800a4a8(&DAT_0800fc26,_DAT_2000087a);
      fw_0800a4a8(&DAT_0800fc28,_DAT_2000087c);
      fw_0800a4a8(&DAT_0800fc2a,DAT_200008cb);
      fw_0800a4b4(&DAT_0800fc2c,_DAT_2000088c);
      fw_0800a4b4(&DAT_0800fc30,_DAT_20000890);
      fw_0800a4a8(&DAT_0800fc3c,_DAT_200008be);
      fw_0800a4a8(&DAT_0800fc3e,_DAT_200008bc);
      fw_0800a4b4(&DAT_0800fc34,_DAT_20000898);
      fw_0800a4b4(&DAT_0800fc38,_DAT_200008b8);
      fw_0800a4a8(&DAT_0800fc58,(short)DAT_20000102);
      fw_0800a4a8(&DAT_0800fc5a,_DAT_2000010c);
      fw_0800a4a8(&DAT_0800fc5c,_DAT_20000118 & 0xffff);
      fw_0800a4a8(&DAT_0800fc5e,0xc136);
      uVar2 = 0;
      do {
        iVar5 = uVar2 * 0x34;
        *(undefined4 *)(iVar5 + 0x200005e4) = 0;
        *(undefined4 *)(iVar5 + 0x200005ec) = 0;
        *(undefined1 *)(iVar5 + 0x20000617) = 0;
        fw_08009e14(uVar2 & 0xff);
        *(undefined2 *)(uVar2 * 2 + 0x200008a0) = 200;
        fw_0800a4a8(&DAT_0800fc40 + uVar2 * 2,*(undefined2 *)(uVar2 * 2 + 0x200008a0));
        fw_0800a5b0(uVar2 & 0xff);
        uVar2 = uVar2 + 1 & 0xffff;
      } while (uVar2 < 0xc);
      return;
    }
    bVar6 = uVar2 == 0x3ec9;
  } while (!bVar6);
  _DAT_20000856 = fw_08005340(&DAT_0800fc02);
  _DAT_20000858 = fw_08005340(&DAT_0800fc04);
  _DAT_2000085c = fw_08005340(&DAT_0800fc06);
  _DAT_2000085e = fw_08005340(&DAT_0800fc08);
  _DAT_2000085a = fw_08005340(&DAT_0800fc0a);
  uVar2 = 0;
  do {
    iVar5 = uVar2 * 2;
    uVar1 = fw_08005340(&DAT_0800fc0c + iVar5);
    puVar4 = &DAT_20000854 + iVar5;
    *(undefined2 *)(&DAT_20000860 + iVar5) = uVar1;
    if (uVar2 < 3) {
      uVar1 = fw_08005340(&DAT_0800fc14 + iVar5);
      *(undefined2 *)(puVar4 + 0x14) = uVar1;
    }
    uVar2 = uVar2 + 1 & 0xffff;
  } while (uVar2 < 4);
  _DAT_2000086e = fw_08005340(&DAT_0800fc1a);
  _DAT_20000870 = fw_08005340(&DAT_0800fc1c);
  _DAT_20000872 = fw_08005340(&DAT_0800fc1e);
  _DAT_20000874 = fw_08005340(&DAT_0800fc20);
  _DAT_20000876 = fw_08005340(&DAT_0800fc22);
  _DAT_20000878 = fw_08005340(&DAT_0800fc24);
  _DAT_2000087a = fw_08005340(&DAT_0800fc26);
  _DAT_2000087c = fw_08005340(&DAT_0800fc28);
  DAT_200008cb = fw_08005340(&DAT_0800fc2a);
  _DAT_2000087e = 0x2d0;
  _DAT_200008c8 = 1;
  _DAT_2000088c = fw_08005344(&DAT_0800fc2c);
  _DAT_20000890 = fw_08005344(&DAT_0800fc30);
  _DAT_20000898 = fw_08005344(&DAT_0800fc34);
  _DAT_200008be = fw_08005340(&DAT_0800fc3c);
  _DAT_200008bc = fw_08005340(&DAT_0800fc3e);
  _DAT_200008b8 = fw_08005344(&DAT_0800fc38);
  DAT_20000102 = fw_08005340(&DAT_0800fc58);
  _DAT_2000010c = fw_08005340(&DAT_0800fc5a);
  _DAT_20000118 = fw_08005340(&DAT_0800fc5c);
  if (_DAT_2000087e < _DAT_20000856) {
    _DAT_20000856 = 0xf0;
  }
  if (_DAT_2000087e < _DAT_20000858) {
    _DAT_20000858 = 0xf0;
  }
  if (999 < _DAT_2000085c) {
    _DAT_2000085c = 10;
  }
  if (999 < _DAT_2000085e) {
    _DAT_2000085e = 10;
  }
  if (0xfa < _DAT_2000085a) {
    _DAT_2000085a = 10;
  }
  if (999999 < _DAT_2000088c) {
    _DAT_2000088c = 0;
  }
  if (999999 < _DAT_20000890) {
    _DAT_20000890 = 0;
  }
  if (999999 < _DAT_20000898) {
    _DAT_20000898 = 0;
  }
  _DAT_20000894 = _DAT_2000088c + _DAT_20000890;
  uVar2 = 0;
  do {
    iVar5 = uVar2 * 2;
    uVar3 = fw_08005340(&DAT_0800fc40 + iVar5);
    *(short *)(iVar5 + 0x200008a0) = (short)uVar3;
    if (2000 < uVar3) {
      *(undefined2 *)(iVar5 + 0x200008a0) = 200;
    }
    fw_0800a4dc(uVar2 & 0xff);
    uVar2 = uVar2 + 1 & 0xffff;
  } while (uVar2 < 0xc);
  return;
}

