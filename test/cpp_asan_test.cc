#include "encap.h"
#include "deencap.h"
#include "virtual_fragment.h"

int main() {
  gse_encap_t* encap = nullptr;
  gse_deencap_t* deencap = nullptr;
  gse_vfrag_t* vfrag = nullptr;

  if (gse_encap_init(1, 8, &encap) != GSE_STATUS_OK) {
    return 1;
  }
  if (gse_deencap_init(1, &deencap) != GSE_STATUS_OK) {
    gse_encap_release(encap);
    return 2;
  }
  if (gse_create_vfrag(&vfrag, 8, 0, 0) != GSE_STATUS_OK) {
    gse_encap_release(encap);
    gse_deencap_release(deencap);
    return 3;
  }

  gse_free_vfrag(&vfrag);
  gse_encap_release(encap);
  gse_deencap_release(deencap);
  return 0;
}
