include_guard_x()

set(CK_DIR ${CMAKE_SOURCE_DIR}/deps/ck)

set(RTM_ENABLE "CK_MD_RTM_DISABLE")
set(LSE_ENABLE "CK_MD_LSE_DISABLE")
set(POINTER_PACK_ENABLE "CK_MD_POINTER_PACK_DISABLE")
set(VMA_BITS "unknown")
set(MM "CK_MD_TSO")
set(DISABLE_DOUBLE "CK_PR_ENABLE_DOUBLE")

configure_file(
        ${CK_DIR}/include/ck_md.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/include/ck_md.h
)

add_library(ck STATIC
        ${CK_DIR}/src/ck_array.c
        ${CK_DIR}/src/ck_barrier_centralized.c
        ${CK_DIR}/src/ck_barrier_combining.c
        ${CK_DIR}/src/ck_barrier_dissemination.c
        ${CK_DIR}/src/ck_barrier_mcs.c
        ${CK_DIR}/src/ck_barrier_tournament.c
        ${CK_DIR}/src/ck_epoch.c
        ${CK_DIR}/src/ck_hp.c
        ${CK_DIR}/src/ck_hs.c
        ${CK_DIR}/src/ck_ht.c
        ${CK_DIR}/src/ck_ht_hash.h
        ${CK_DIR}/src/ck_internal.h
        ${CK_DIR}/src/ck_rhs.c
        )

target_include_directories(ck
        PRIVATE ${CK_DIR}/src
        PRIVATE ${CK_DIR}/include
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include
        )

target_include_directories(ck
        SYSTEM INTERFACE ${CK_DIR}/include
        )
