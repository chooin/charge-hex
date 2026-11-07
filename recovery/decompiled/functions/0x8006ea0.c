// rea decompile_all
// name: fw_08006ea0
// address: 0x8006ea0
// body: available
// range: 0x8006ea0-0x8006fab inclusive
// range: 0x8006fae-0x8007099 inclusive
// non_contiguous: true
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


void fw_08006ea0(int *param_1)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  code *pcVar5;
  uint *puVar6;
  uint *puVar7;
  uint uVar8;
  
  puVar6 = (uint *)*param_1;
  uVar2 = puVar6[7];
  uVar4 = *puVar6;
  uVar8 = puVar6[2];
  if ((uVar2 & 0x80f) == 0) {
    if ((-1 < (int)(uVar2 << 0x1a)) || (-1 < (int)(uVar4 << 0x1a))) goto LAB_08006fba;
    pcVar5 = (code *)param_1[0x19];
  }
  else {
    if ((uVar8 & 1) != 0 || (uVar4 & 0x4000120) != 0) {
      puVar7 = (uint *)(param_1 + 0x20);
      if (((uVar2 & 1) != 0) && ((int)(uVar4 << 0x17) < 0)) {
        puVar6[8] = 1;
        *puVar7 = *puVar7 | 1;
      }
      if (((int)(uVar2 << 0x1e) < 0) && ((uVar8 & 1) != 0)) {
        *(undefined4 *)(*param_1 + 0x20) = 2;
        *puVar7 = *puVar7 | 4;
      }
      if (((int)(uVar2 << 0x1d) < 0) && ((uVar8 & 1) != 0)) {
        *(undefined4 *)(*param_1 + 0x20) = 4;
        *puVar7 = *puVar7 | 2;
      }
      if (((int)(uVar2 << 0x1c) < 0) && ((uVar4 & 0x20) != 0 || (uVar8 & 1) != 0)) {
        *(undefined4 *)(*param_1 + 0x20) = 8;
        *puVar7 = *puVar7 | 8;
      }
      if (((int)(uVar2 << 0x14) < 0) && ((int)(uVar4 << 5) < 0)) {
        *(undefined4 *)(*param_1 + 0x20) = 0x800;
        *puVar7 = *puVar7 | 0x20;
      }
      if (*puVar7 == 0) {
        return;
      }
      if ((((int)(uVar2 << 0x1a) < 0) && ((int)(uVar4 << 0x1a) < 0)) &&
         ((code *)param_1[0x19] != (code *)0x0)) {
        (*(code *)param_1[0x19])(param_1);
      }
      if ((-1 < *(int *)(*param_1 + 8) << 0x19) && ((*puVar7 & 0x28) == 0)) {
        fw_08006e64(param_1);
        *puVar7 = 0;
        return;
      }
      fw_080091c4(param_1);
      iVar3 = *param_1;
      if (-1 < *(int *)(iVar3 + 8) << 0x19) {
LAB_08006fa4:
        fw_08006e64(param_1);
        return;
      }
      *(uint *)(iVar3 + 8) = *(uint *)(iVar3 + 8) & 0xffffffbf;
      if (param_1[0x1c] == 0) goto LAB_08006fa4;
      *(undefined4 *)(param_1[0x1c] + 0x34) = 0x80090b5;
      iVar3 = fw_08005884(param_1[0x1c]);
      if (iVar3 == 0) {
        return;
      }
      param_1 = (int *)param_1[0x1c];
      pcVar5 = (code *)param_1[0xd];
      goto LAB_08006fa0;
    }
LAB_08006fba:
    if (((param_1[0x18] == 1) && ((int)(uVar2 << 0x1b) < 0)) && ((int)(uVar4 << 0x1b) < 0)) {
      puVar6[8] = 0x10;
      puVar6 = (uint *)*param_1;
      if ((int)(puVar6[2] * 0x2000000) < 0) {
        uVar2 = *(uint *)(*(int *)param_1[0x1c] + 4);
        uVar4 = uVar2 & 0xffff;
        if (uVar4 == 0) {
          return;
        }
        if (*(ushort *)(param_1 + 0x16) <= uVar4) {
          return;
        }
        *(short *)((int)param_1 + 0x5a) = (short)uVar2;
        if (((int *)param_1[0x1c])[6] != 0x20) {
          *puVar6 = *puVar6 & 0xfffffeff;
          *(uint *)(*param_1 + 8) = *(uint *)(*param_1 + 8) & 0xfffffffe;
          *(uint *)(*param_1 + 8) = *(uint *)(*param_1 + 8) & 0xffffffbf;
          param_1[0x1f] = 0x20;
          param_1[0x18] = 0;
          *(uint *)*param_1 = *(uint *)*param_1 & 0xffffffef;
          fw_08005844(param_1[0x1c]);
        }
        sVar1 = (short)param_1[0x16] - *(short *)((int)param_1 + 0x5a);
      }
      else {
        sVar1 = (short)param_1[0x16] - *(short *)((int)param_1 + 0x5a);
        if (*(short *)((int)param_1 + 0x5a) == 0) {
          return;
        }
        if (sVar1 == 0) {
          return;
        }
        *puVar6 = *puVar6 & 0xfffffedf;
        *(uint *)(*param_1 + 8) = *(uint *)(*param_1 + 8) & 0xfffffffe;
        param_1[0x1f] = 0x20;
        param_1[0x18] = 0;
        param_1[0x19] = 0;
        *(uint *)*param_1 = *(uint *)*param_1 & 0xffffffef;
      }
      fw_08006e28(param_1,sVar1);
      return;
    }
    if ((-1 < (int)(uVar2 << 0x18)) || (-1 < (int)(uVar4 << 0x18))) {
      if (-1 < (int)(uVar2 << 0x19)) {
        return;
      }
      if (-1 < (int)(uVar4 << 0x19)) {
        return;
      }
      *puVar6 = *puVar6 & 0xffffffbf;
      param_1[0x1e] = 0x20;
      param_1[0x1a] = 0;
      fw_08007330();
      return;
    }
    pcVar5 = (code *)param_1[0x1a];
  }
  if (pcVar5 == (code *)0x0) {
    return;
  }
LAB_08006fa0:
  (*pcVar5)(param_1);
  return;
}

