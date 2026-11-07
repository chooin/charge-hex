// rea decompile_all
// name: fw_080057e8
// address: 0x80057e8
// body: available
// range: 0x80057e8-0x800583d inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


int fw_080057e8(int *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  if ((-1 < *(int *)(*param_1 + 8) << 0x1d) && ((char)param_1[0xd] != '\x01')) {
    *(undefined1 *)(param_1 + 0xd) = 1;
    if ((*(char *)((int)param_1 + 0x19) == '\x01') || (iVar1 = fw_08004554(param_1), iVar1 == 0)) {
      param_1[0xe] = param_1[0xe] & 0xfffff1feU | 0x100;
      param_1[0xf] = 0;
      *(undefined1 *)(param_1 + 0xd) = 0;
      *(undefined4 *)*param_1 = 0x1c;
      *(uint *)(*param_1 + 8) = *(uint *)(*param_1 + 8) | 4;
    }
    return iVar1;
  }
  return 2;
}

