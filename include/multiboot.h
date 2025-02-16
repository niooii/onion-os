#include <def.h>

// refer to:
// https://www.gnu.org/software/grub/manual/multiboot/html_node/Boot-information-format.html

// for framebuffer
struct multiboot_color {
    uint8_t red_field_position;
    uint8_t red_mask_size;
    uint8_t green_field_position;
    uint8_t green_mask_size;
    uint8_t blue_field_position;
    uint8_t blue_mask_size;
} __attribute__((packed));

struct multiboot_aout_symbol_table {
    uint32_t tabsize;
    uint32_t strsize;
    uint32_t addr;
    uint32_t reserved;
} __attribute__((packed));

struct multiboot_elf_section_header_table {
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;
} __attribute__((packed));

struct multiboot_info {
    uint32_t flags;

    // Memory info (flags[0])
    uint32_t mem_lower;
    uint32_t mem_upper;

    // Boot device (flags[1])
    uint32_t boot_device;

    // Command line (flags[2])
    uint32_t cmdline;

    // Modules (flags[3])
    uint32_t mods_count;
    uint32_t mods_addr;

    // Symbol information (flags[4] or flags[5])
    union {
        struct multiboot_aout_symbol_table        aout_sym;
        struct multiboot_elf_section_header_table elf_sec;
    } sym;

    // Memory mapping (flags[6])
    uint32_t mmap_length;
    uint32_t mmap_addr;

    // Drive info (flags[7])
    uint32_t drives_length;
    uint32_t drives_addr;

    // ROM configuration table (flags[8])
    uint32_t config_table;

    // Boot loader name (flags[9])
    uint32_t boot_loader_name;

    // APM table (flags[10])
    uint32_t apm_table;

    // Video info (flags[11])
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;

    // Framebuffer info (flags[12])
    uint64_t               framebuffer_addr;
    uint32_t               framebuffer_pitch;
    uint32_t               framebuffer_width;
    uint32_t               framebuffer_height;
    uint8_t                framebuffer_bpp;
    uint8_t                framebuffer_type;
    struct multiboot_color color_info;
} __attribute__((packed));

/* Flag bit positions */
#define MULTIBOOT_BIT_MEMORY           0x00000001
#define MULTIBOOT_BIT_BOOTDEV          0x00000002
#define MULTIBOOT_BIT_CMDLINE          0x00000004
#define MULTIBOOT_BIT_MODS             0x00000008
#define MULTIBOOT_BIT_AOUT_SYMS        0x00000010
#define MULTIBOOT_BIT_ELF_SHDR         0x00000020
#define MULTIBOOT_BIT_MEM_MAP          0x00000040
#define MULTIBOOT_BIT_DRIVE_INFO       0x00000080
#define MULTIBOOT_BIT_CONFIG_TABLE     0x00000100
#define MULTIBOOT_BIT_BOOT_LOADER_NAME 0x00000200
#define MULTIBOOT_BIT_APM_TABLE        0x00000400
#define MULTIBOOT_BIT_VBE_INFO         0x00000800
#define MULTIBOOT_BIT_FRAMEBUFFER_INFO 0x00001000
void some_callback(int (*callback)(int, int));
