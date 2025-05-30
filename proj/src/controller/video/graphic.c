#include "graphic.h"

vbe_mode_info_t vbe_info;

int (set_graphic_mode)(uint16_t submode)
{
    reg86_t reg86;

    memset(&reg86, 0, sizeof(reg86));

    reg86.intno = 0x10;
    reg86.ax = 0x4F02;
    reg86.bx = submode | BIT(14);

    if (sys_int86(&reg86) != 0) return 1;

    return 0;
}

int (set_text_mode)()
{
    reg86_t reg86;

    memset(&reg86, 0, sizeof(reg86));

    reg86.intno = 0x10;
    reg86.ax = 0x0003;
    reg86.bx = 0x0000;

    if (sys_int86(&reg86) != 0) return 1;

    return 0;
}

int (set_frame_buffer)(uint16_t mode, uint8_t **frame_buffer)
{
    memset(&vbe_info, 0, sizeof(vbe_info));
    if (vbe_get_mode_info(mode, &vbe_info) != 0) return 1;

    unsigned int bytes_per_pixel = (vbe_info.BitsPerPixel + 7) / 8;
    unsigned int frame_size = vbe_info.XResolution * vbe_info.YResolution * bytes_per_pixel;

    struct minix_mem_range mr;
    mr.mr_base = vbe_info.PhysBasePtr;
    mr.mr_limit = mr.mr_base + frame_size;

    if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr) != 0) return 1;

    *frame_buffer = vm_map_phys(SELF, (void*) mr.mr_base, frame_size);

    return *frame_buffer == NULL ? 1 : 0;
}

int (draw_pixel)(uint16_t x, uint16_t y, uint32_t color, uint8_t *buffer)
{
    if (x >= vbe_info.XResolution || y >= vbe_info.YResolution) return 1;

    unsigned int bytes_per_pixel = (vbe_info.BitsPerPixel + 7) / 8;
    unsigned int index = (vbe_info.XResolution * y + x) * bytes_per_pixel;

    memcpy(&buffer[index], &color, bytes_per_pixel);

    return 0;
}

int (draw_line)(uint16_t x, uint16_t y, uint16_t len, uint32_t color, uint8_t *buffer)
{
    for (unsigned int i = 0; i < len; i++)
        if (draw_pixel(x + i, y, color, buffer) != 0) return 1;
    return 0;
}

int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color, uint8_t *buffer)
{
    for (unsigned int i = 0; i < height; i++)
        if (draw_line(x, y + i, width, color, buffer) != 0) return 1;
    return 0;
}

int (draw_XPM)(xpm_map_t xpm, uint16_t x, uint16_t y, uint8_t *buffer)
{
    xpm_image_t img;
    uint8_t* colors = xpm_load(xpm, XPM_INDEXED, &img);

    for (int h = 0; h < img.height; h++)
    {
        for (int w = 0; w < img.width; w++)
        {
            if (draw_pixel(x + w, y + h, *colors, buffer) != 0) return 1;
            colors++;
        }
    }

    return 0;
}
