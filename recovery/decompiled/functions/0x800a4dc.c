// rea decompile_all
// name: fw_0800a4dc
// address: 0x800a4dc
// body: available
// range: 0x800a4dc-0x800a5a7 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


void fw_0800a4dc(uint param_1)

{
  int iVar1;
  undefined1 local_28;
  byte local_27;
  undefined1 local_26;
  undefined2 local_25;
  undefined2 local_23;
  undefined4 local_21;
  undefined2 local_1d;
  undefined4 local_1b;
  undefined2 local_17;
  undefined4 local_15;
  
  if (param_1 < 0xc) {
    fw_08007498(param_1 * 0x17 + 0xf000 & 0xffff,&local_28,0x17);
    iVar1 = param_1 * 0x34;
    *(undefined1 *)(iVar1 + 0x200005f9) = local_28;
    *(ushort *)(iVar1 + 0x2000060e) = (ushort)local_27;
    *(undefined1 *)(iVar1 + 0x20000616) = local_26;
    *(undefined2 *)(iVar1 + 0x200005fc) = local_25;
    *(undefined2 *)(iVar1 + 0x200005fe) = local_23;
    *(undefined4 *)(iVar1 + 0x20000608) = local_21;
    *(undefined2 *)(iVar1 + 0x200005f0) = local_1d;
    *(undefined4 *)(iVar1 + 0x200005e4) = local_1b;
    *(undefined2 *)(iVar1 + 0x200005ea) = local_17;
    fw_08009fc4(param_1);
    *(undefined4 *)(iVar1 + 0x20000604) = local_15;
    *(uint *)(iVar1 + 0x200005ec) = (uint)*(ushort *)(iVar1 + 0x200005ea) * 36000;
  }
  return;
}

