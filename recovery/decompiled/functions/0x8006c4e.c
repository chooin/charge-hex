// rea decompile_all
// name: fw_08006c4e
// address: 0x8006c4e
// body: available
// range: 0x8006c4e-0x8006daf inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


void fw_08006c4e(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if ((-1 < (int)(~*(uint *)(iVar1 + 0x10) * 0x40000000)) &&
     (-1 < (int)(~*(uint *)(iVar1 + 0xc) << 0x1e))) {
    *(undefined4 *)(iVar1 + 0x10) = 0xfffffffd;
    *(undefined1 *)(param_1 + 7) = 1;
    if ((*(uint *)(*param_1 + 0x18) & 3) == 0) {
      fw_08006db0(param_1);
      fw_08006db2(param_1);
    }
    else {
      fw_08006c4c();
    }
    *(undefined1 *)(param_1 + 7) = 0;
  }
  iVar1 = *param_1;
  if ((-1 < (int)(~*(uint *)(iVar1 + 0x10) << 0x1d)) &&
     (-1 < (int)(~*(uint *)(iVar1 + 0xc) << 0x1d))) {
    *(undefined4 *)(iVar1 + 0x10) = 0xfffffffb;
    *(undefined1 *)(param_1 + 7) = 2;
    if ((*(uint *)(*param_1 + 0x18) & 0x3ff) >> 8 == 0) {
      fw_08006db0(param_1);
      fw_08006db2(param_1);
    }
    else {
      fw_08006c4c();
    }
    *(undefined1 *)(param_1 + 7) = 0;
  }
  iVar1 = *param_1;
  if ((-1 < (int)(~*(uint *)(iVar1 + 0x10) << 0x1c)) &&
     (-1 < (int)(~*(uint *)(iVar1 + 0xc) << 0x1c))) {
    *(undefined4 *)(iVar1 + 0x10) = 0xfffffff7;
    *(undefined1 *)(param_1 + 7) = 4;
    if ((*(uint *)(*param_1 + 0x1c) & 3) == 0) {
      fw_08006db0(param_1);
      fw_08006db2(param_1);
    }
    else {
      fw_08006c4c();
    }
    *(undefined1 *)(param_1 + 7) = 0;
  }
  iVar1 = *param_1;
  if ((-1 < (int)(~*(uint *)(iVar1 + 0x10) << 0x1b)) &&
     (-1 < (int)(~*(uint *)(iVar1 + 0xc) << 0x1b))) {
    *(undefined4 *)(iVar1 + 0x10) = 0xffffffef;
    *(undefined1 *)(param_1 + 7) = 8;
    if ((*(uint *)(*param_1 + 0x1c) & 0x3ff) >> 8 == 0) {
      fw_08006db0(param_1);
      fw_08006db2(param_1);
    }
    else {
      fw_08006c4c();
    }
    *(undefined1 *)(param_1 + 7) = 0;
  }
  iVar1 = *param_1;
  if (((~*(uint *)(iVar1 + 0x10) & 1) == 0) && ((~*(uint *)(iVar1 + 0xc) & 1) == 0)) {
    *(undefined4 *)(iVar1 + 0x10) = 0xfffffffe;
    fw_08006db4(param_1);
  }
  iVar1 = *param_1;
  if ((-1 < (int)(~*(uint *)(iVar1 + 0x10) << 0x18)) &&
     (-1 < (int)(~*(uint *)(iVar1 + 0xc) << 0x18))) {
    *(undefined4 *)(iVar1 + 0x10) = 0xffffff7f;
    fw_08006a50(param_1);
  }
  iVar1 = *param_1;
  if ((-1 < (int)(~*(uint *)(iVar1 + 0x10) << 0x19)) &&
     (-1 < (int)(~*(uint *)(iVar1 + 0xc) << 0x19))) {
    *(undefined4 *)(iVar1 + 0x10) = 0xffffffbf;
    fw_08006dc8(param_1);
  }
  iVar1 = *param_1;
  if ((-1 < (int)(~*(uint *)(iVar1 + 0x10) << 0x1a)) &&
     (-1 < (int)(~*(uint *)(iVar1 + 0xc) << 0x1a))) {
    *(undefined4 *)(iVar1 + 0x10) = 0xffffffdf;
    fw_08006a52(param_1);
  }
  return;
}

