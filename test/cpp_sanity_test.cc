#include <type_traits>

#include "encap.h"
#include "deencap.h"
#include "status.h"
#include "virtual_fragment.h"

static_assert(std::is_same_v<const char*, decltype(gse_get_status(GSE_STATUS_OK))>);

int main() {
  gse_encap_t* encap = nullptr;
  gse_deencap_t* deencap = nullptr;
  gse_vfrag_t* vfrag = nullptr;

  (void)gse_encap_init(1, 1, &encap);
  (void)gse_deencap_init(1, &deencap);
  (void)gse_create_vfrag(&vfrag, 1, 0, 0);

  if (vfrag != nullptr) {
    gse_free_vfrag(&vfrag);
  }
  if (encap != nullptr) {
    gse_encap_release(encap);
  }
  if (deencap != nullptr) {
    gse_deencap_release(deencap);
  }

  return 0;
}
