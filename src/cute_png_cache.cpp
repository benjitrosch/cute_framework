/*
	Cute Framework
	Copyright (C) 2020 Randy Gaul https://randygaul.net

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	   claim that you wrote the original software. If you use this software
	   in a product, an acknowledgment in the product documentation would be
	   appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
	   misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/

#include <cute_png_cache.h>
#include <cute_image.h>
#include <cute_sprite.h>

#include <internal/cute_png_cache_internal.h>
#include <internal/cute_app_internal.h>

#define INJECT(s) cf_strpool_inject(cache->strpool, s, (int)CUTE_STRLEN(s))

static void cf_s_get_pixels(uint64_t image_id, void* buffer, int bytes_to_fill, void* udata)
{
	cf_png_cache_t* cache = (cf_png_cache_t*)udata;
	void* pixels = NULL;
	if (cache->id_to_pixels.find(image_id, &pixels).is_error()) {
		CUTE_DEBUG_PRINTF("png cache -- unable to find id %lld.", (long long int)image_id);
		CUTE_MEMSET(buffer, 0, bytes_to_fill);
	} else {
		CUTE_MEMCPY(buffer, pixels, bytes_to_fill);
	}
}

cf_png_cache_t* cf_png_cache_make(void* mem_ctx)
{
	cf_png_cache_t* cache = CUTE_NEW(cf_png_cache_t, cf_app->mem_ctx);
	cache->strpool = cf_make_strpool(mem_ctx);
	cache->mem_ctx = mem_ctx;
	return cache;
}

void cf_png_cache_destroy(cf_png_cache_t* cache)
{
	int animation_count = cache->animations.count();
	cf_animation_t** animations = cache->animations.items();
	for (int i = 0; i < animation_count; ++i) {
		animations[i]->~cf_animation_t();
		CUTE_FREE(animations[i], cache->mem_ctx);
	}

	int table_count = cache->animation_tables.count();
	cf_animation_table_t** tables = cache->animation_tables.items();
	for (int i = 0; i < table_count; ++i) {
		tables[i]->~cf_animation_table_t();
		CUTE_FREE(tables[i], cache->mem_ctx);
	}

	while (cache->pngs.count()) {
		cf_png_t png = cache->pngs.items()[0];
		cf_png_cache_unload(cache, &png);
	}

	cf_destroy_strpool(cache->strpool);
	void* mem_ctx = cache->mem_ctx;
	cache->~cf_png_cache_t();
	CUTE_FREE(cache, mem_ctx);
}

cf_error_t cf_png_cache_load(cf_png_cache_t* cache, const char* png_path, cf_png_t* png)
{
	cf_image_t img;
	cf_error_t err = cf_image_load_png(png_path, &img, cache->mem_ctx);
	if (err.is_error()) return err;
	cf_png_t entry;
	entry.path = cf_strpool_cstr(cache->strpool, INJECT(png_path));
	entry.id = cache->id_gen++;
	entry.pix = img.pix;
	entry.w = img.w;
	entry.h = img.h;
	cache->id_to_pixels.insert(entry.id, img.pix);
	cache->pngs.insert(entry.id, entry);
	if (png) *png = entry;
	return cf_error_success();
}

cf_error_t cf_png_cache_load_mem(cf_png_cache_t* cache, const char* png_path, const void* memory, size_t size, cf_png_t* png)
{
	cf_image_t img;
	cf_error_t err = cf_image_load_png_mem(memory, (int)size, &img, cache->mem_ctx);
	if (err.is_error()) return err;
	cf_png_t entry;
	entry.path = cf_strpool_cstr(cache->strpool, INJECT(png_path));
	entry.id = cache->id_gen++;
	entry.pix = img.pix;
	entry.w = img.w;
	entry.h = img.h;
	cache->id_to_pixels.insert(entry.id, img.pix);
	cache->pngs.insert(entry.id, entry);
	if (png) *png = entry;
	return cf_error_success();
}

void cf_png_cache_unload(cf_png_cache_t* cache, cf_png_t* png)
{
	cf_image_t img;
	img.pix = png->pix;
	img.w = png->w;
	img.h = png->h;
	cf_image_free(&img);
	cache->id_to_pixels.remove(png->id);
	cache->pngs.remove(png->id);
	CUTE_MEMSET(png, 0, sizeof(*png));
}

cf_get_pixels_fn* cf_png_cache_get_pixels_fn(cf_png_cache_t* cache)
{
	return cf_s_get_pixels;
}

cf_strpool_t* cf_png_cache_get_strpool_ptr(cf_png_cache_t* cache)
{
	return cache->strpool;
}

const cf_animation_t* cf_png_cache_make_animation(cf_png_cache_t* cache, const char* name, const cf_array<cf_png_t>& pngs, const cf_array<float>& delays)
{
	CUTE_ASSERT(pngs.count() == delays.count());
	cf_strpool_id name_id = INJECT(name);

	// If already made, just return the old animation.
	cf_animation_t* animation;
	if (!cache->animations.find(name_id, &animation).is_error()) {
		return animation;
	}

	// Otherwise allocate a new animation.
	cf_animation_t** animation_ptr = cache->animations.insert(name_id);
	animation = (cf_animation_t*)CUTE_ALLOC(sizeof(cf_animation_t), cache->mem_ctx);
	CUTE_PLACEMENT_NEW(animation) cf_animation_t;
	*animation_ptr = animation;

	animation->name = cf_strpool_cstr(cache->strpool, name_id);

	for (int i = 0; i < pngs.count(); ++i) {
		cf_frame_t frame;
		frame.id = pngs[i].id;
		frame.delay = delays[i];
		animation->frames.add(frame);
	}

	return animation;
}

 const cf_animation_t* cf_png_cache_get_animation(cf_png_cache_t* cache, const char* name)
{
	cf_animation_t* animation;
	if (!cache->animations.find(INJECT(name), &animation).is_error()) {
		return animation;
	} else {
		return NULL;
	}
}

const cf_animation_table_t* cf_png_cache_make_animation_table(cf_png_cache_t* cache, const char* sprite_name, const cf_array<const cf_animation_t*>& animations)
{
	cf_strpool_id name_id = INJECT(sprite_name);

	// If already made, just return the old table.
	cf_animation_table_t* table;
	if (!cache->animation_tables.find(name_id, &table).is_error()) {
		return table;
	}

	// Otherwise allocate a new table.
	cf_animation_table_t** table_ptr = cache->animation_tables.insert(name_id);
	table = (cf_animation_table_t*)CUTE_ALLOC(sizeof(cf_animation_table_t), cache->mem_ctx);
	CUTE_PLACEMENT_NEW(table) cf_animation_table_t;
	*table_ptr = table;

	for (int i = 0; i < animations.count(); ++i) {
		table->insert(animations[i]->name, animations[i]);
	}

	return table;
}

const cf_animation_table_t* cf_png_cache_get_animation_table(cf_png_cache_t* cache, const char* sprite_name)
{
	cf_animation_table_t* table;
	if (!cache->animation_tables.find(INJECT(sprite_name), &table).is_error()) {
		return table;
	} else {
		return NULL;
	}
}

cf_sprite_t cf_png_cache_make_sprite(cf_png_cache_t* cache, const char* sprite_name, const cf_animation_table_t* table)
{
	cf_strpool_id name_id = INJECT(sprite_name);
	if (!table) {
		cf_error_t err = cache->animation_tables.find(name_id, (cf_animation_table_t**)&table);
		CUTE_ASSERT(!err.is_error());
	}

	cf_png_t png;
	cf_error_t err = cache->pngs.find(table->items()[0]->frames[0].id, &png);
	CUTE_ASSERT(!err.is_error());

	cf_sprite_t sprite;
	sprite.name = cf_strpool_cstr(cache->strpool, name_id);
	sprite.w = png.w;
	sprite.h = png.h;
	sprite.animations = table;
	sprite.play((const char*)sprite.animations->keys()[0].data);

	return sprite;
}
