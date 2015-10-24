#ifndef PKMN_OBJECTS_H_
#define PKMN_OBJECTS_H_

#include "types.h"

struct object;
typedef void (*object_callback)(struct object*);

struct coords8 {
	u8 x;
	u8 y;
};

struct coords16 {
	u16 x;
	u16 y;
};

struct frame {
	u16 data;
	u16 duration;
};

struct rotscale_frame {
	u16 scale_delta_x;
	u16 scale_delta_y;
	u8 rot_delta;
	u8 duration;
	u16 field_6;
};

struct sprite {
	u16 attr0;
	u16 attr1;
	u16 attr2;
	u16 rotscale;
};

struct graphics {
	u8* address;
	u32 size;
};

struct template {
	u16 tiles_tag;
	u16 pal_tag;
	struct sprite *oam;
	struct frame **animation;
	struct graphics *graphics;
	struct rotscale_frame **rotscale;
	object_callback callback;
};

struct object {
	struct sprite final_oam;
	struct frame **animation_table;
	struct graphics *gfx_table;
	struct rotscale_frame *rotscale_table;
	struct template *template;
	u32 field18;
	object_callback callback;
	struct coords16 pos1;
	struct coords16 pos2;
	struct coords8 shift;
	u8 anim_number;
	u8 anim_frame;
	u8 anim_delay;
	u8 counter;
	u16 private[8];
	u8 bitfield2;
	u8 bitfield;
	u16 anim_data_offset;
	u8 field42;
	u8 y_height_related;
};

struct object objects[64];

#endif /* PKMN_OBJECTS_H_ */
