#pragma once

#include <stdint.h>
#include <stdbool.h>

struct wl_output;

enum frame_capture_status {
	CAPTURE_STOPPED = 0,
	CAPTURE_IN_PROGRESS,
	CAPTURE_FAILED,
	CAPTURE_FATAL,
	CAPTURE_DONE,
};

struct frame_capture {
	enum frame_capture_status status;

	bool overlay_cursor;
	struct wl_output* wl_output;

	void* userdata;
	void (*on_done)(struct frame_capture*);

	struct {
		uint32_t fourcc_format;
		uint32_t width;
		uint32_t height;
		uint32_t stride;
	} frame_info;

	struct {
		uint32_t x;
		uint32_t y;
		uint32_t width;
		uint32_t height;
	} damage_hint;

	struct {
		int (*start)(struct frame_capture*);
		void (*stop)(struct frame_capture*);
	} backend;
};

static inline int frame_capture_start(struct frame_capture* self)
{
	return self->backend.start(self);
}

static inline void frame_capture_stop(struct frame_capture* self)
{
	self->backend.stop(self);
}
