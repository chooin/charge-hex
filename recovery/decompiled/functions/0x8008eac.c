// rea decompile_all
// name: fw_08008eac
// address: 0x8008eac
// body: available
// range: 0x8008eac-0x8008f79 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


void fw_08008eac(uint param_1)

{
  char cVar1;
  uint uVar2;
  
  uVar2 = (uint)DAT_20000126;
  cVar1 = (char)param_1;
  if (uVar2 != 0) {
    if (uVar2 != 1) {
      if (uVar2 == DAT_20000125 - 1) {
        if (DAT_20000124 == '\0') {
          if ((byte)(DAT_20001024 ^ DAT_20001025 ^ DAT_20001026 ^ DAT_20001027 ^ DAT_20001028 ^
                     DAT_20001029 ^ DAT_2000102a ^ DAT_2000102b) == param_1) {
            app_handle_identifier_frame();
          }
        }
        else if ((DAT_20000124 != '\x01') && (DAT_20000124 == '\x02')) {
          for (uVar2 = 0; (int)uVar2 < (int)(DAT_20000125 - 1); uVar2 = uVar2 + 1 & 0xff) {
            param_1 = param_1 ^ (byte)(&DAT_20001024)[uVar2];
          }
          if (param_1 == 0) {
            fw_0800c830(&DAT_20001027);
          }
        }
        DAT_20000126 = 0;
        return;
      }
      (&DAT_20001024)[uVar2] = cVar1;
      DAT_20000126 = DAT_20000126 + 1;
      return;
    }
    if (param_1 != 0xaa) {
      if (DAT_20001024 == 0x55) {
        DAT_20000124 = '\x01';
      }
      else if (DAT_20001024 != 0xaa) {
        DAT_20000126 = 0;
        return;
      }
      DAT_20001025 = cVar1;
      DAT_20000126 = 2;
      DAT_20000125 = cVar1 + '\x02';
      return;
    }
    DAT_20001025 = cVar1;
    DAT_20000126 = 2;
    return;
  }
  if (param_1 == 0x55) {
    DAT_20000124 = 0;
  }
  else {
    if (param_1 == 0x44) {
      DAT_20000124 = 2;
      DAT_20000125 = 0x1b;
      DAT_20000126 = 1;
      DAT_20001024 = 0x44;
      return;
    }
    if (param_1 != 0xaa) {
      DAT_20000126 = 0;
      return;
    }
    DAT_20000124 = 1;
  }
  DAT_20001024 = cVar1;
  DAT_20000126 = 1;
  DAT_20000125 = 9;
  return;
}

