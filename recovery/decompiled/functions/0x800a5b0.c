// rea decompile_all
// name: fw_0800a5b0
// address: 0x800a5b0
// body: available
// range: 0x800a5b0-0x800a63f inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


void fw_0800a5b0(uint param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  
  if (param_1 < 0xc) {
    iVar2 = param_1 * 0x34;
    local_30 = *(undefined1 *)(iVar2 + 0x200005f9);
    local_2f = (undefined1)*(undefined2 *)(iVar2 + 0x2000060e);
    local_2e = *(undefined1 *)(iVar2 + 0x20000616);
    local_2d = (undefined1)*(undefined2 *)(iVar2 + 0x200005fc);
    local_2c = (undefined1)((ushort)*(undefined2 *)(iVar2 + 0x200005fc) >> 8);
    local_2b = (undefined1)*(undefined2 *)(iVar2 + 0x200005fe);
    local_2a = (undefined1)((ushort)*(undefined2 *)(iVar2 + 0x200005fe) >> 8);
    uVar3 = *(undefined4 *)(iVar2 + 0x20000608);
    local_29 = (undefined1)uVar3;
    local_28 = (undefined1)((uint)uVar3 >> 8);
    local_27 = (undefined1)((uint)uVar3 >> 0x10);
    local_26 = (undefined1)((uint)uVar3 >> 0x18);
    local_25 = (undefined1)*(undefined2 *)(iVar2 + 0x200005f0);
    local_24 = (undefined1)((ushort)*(undefined2 *)(iVar2 + 0x200005f0) >> 8);
    uVar3 = *(undefined4 *)(iVar2 + 0x200005e4);
    local_23 = (undefined1)uVar3;
    local_22 = (undefined1)((uint)uVar3 >> 8);
    local_21 = (undefined1)((uint)uVar3 >> 0x10);
    local_20 = (undefined1)((uint)uVar3 >> 0x18);
    uVar1 = fw_08009f88();
    local_1f = (undefined1)uVar1;
    local_1e = (undefined1)((ushort)uVar1 >> 8);
    uVar3 = *(undefined4 *)(iVar2 + 0x20000604);
    local_1d = (undefined1)uVar3;
    local_1c = (undefined1)((uint)uVar3 >> 8);
    local_1b = (undefined1)((uint)uVar3 >> 0x10);
    local_1a = (undefined1)((uint)uVar3 >> 0x18);
    fw_080074fc(param_1 * 0x17 + 0xf000 & 0xffff,&local_30,0x17);
  }
  return;
}

