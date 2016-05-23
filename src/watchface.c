#include <time.h>
#include <stdlib.h>
#include <pebble.h>

// DISCLAIMER: I don't know C very well at all

bool numbers[10][5][4] = {
	{
		{1, 1, 1, 1},
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{1, 1, 1, 1}
	}, 

	{
		{0, 0, 1, 0},
		{0, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 1, 0}
	}, 

	{
		{1, 1, 1, 1},
		{0, 0, 0, 1},
		{1, 1, 1, 1},
		{1, 0, 0, 0},
		{1, 1, 1, 1}
	}, 

	{
		{1, 1, 1, 1},
		{0, 0, 0, 1},
		{0, 1, 1, 1},
		{0, 0, 0, 1},
		{1, 1, 1, 1}
	},

	{
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{1, 1, 1, 1},
		{0, 0, 0, 1},
		{0, 0, 0, 1}
	},

	{
		{1, 1, 1, 1},
		{1, 0, 0, 0},
		{1, 1, 1, 1},
		{0, 0, 0, 1},
		{1, 1, 1, 1}
	}, 

	{
		{1, 1, 1, 1},
		{1, 0, 0, 0},
		{1, 1, 1, 1},
		{1, 0, 0, 1},
		{1, 1, 1, 1}
	}, 

	{
		{1, 1, 1, 1},
		{0, 0, 0, 1},
		{0, 0, 1, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0}
	}, 

	{
		{1, 1, 1, 1},
		{1, 0, 0, 1},
		{1, 1, 1, 1},
		{1, 0, 0, 1},
		{1, 1, 1, 1}
	}, 

	{
		{1, 1, 1, 1},
		{1, 0, 0, 1},
		{1, 1, 1, 1},
		{0, 0, 0, 1},
		{1, 1, 1, 1}
	}
};

static Layer *s_canvas_layer;

int hour = 0;
int minute = 0;

#define COLOR_PALETTES 26
#define COLOR_PARTS 3
GColor colors[COLOR_PALETTES][COLOR_PARTS] = {
	{GColorRed, GColorSunsetOrange, GColorMelon},
	{GColorOrange, GColorRajah, GColorYellow},
	{GColorYellow, GColorPastelYellow, GColorInchworm},
	{GColorGreen, GColorScreaminGreen, GColorSpringBud},
	{GColorGreen, GColorIslamicGreen, GColorDarkGreen},
	{GColorMediumSpringGreen, GColorMalachite, GColorElectricBlue},
	{GColorElectricBlue, GColorCyan, GColorCeleste},
	{GColorCyan, GColorVividCerulean, GColorBlueMoon},
	{GColorBlue, GColorBlueMoon, GColorVividCerulean},
	{GColorIndigo, GColorPurple, GColorPurpureus},
	{GColorMagenta, GColorBrilliantRose, GColorRichBrilliantLavender},
	{GColorFashionMagenta, GColorBrilliantRose, GColorFolly},
	{GColorRed, GColorBulgarianRose, GColorDarkCandyAppleRed},
	{GColorOxfordBlue, GColorBlue, GColorDukeBlue},
	{GColorImperialPurple, GColorPurple, GColorMagenta},
	{GColorMidnightGreen, GColorCadetBlue, GColorCyan},
	{GColorDarkGray, GColorLightGray, GColorBlack},
	{GColorOxfordBlue, GColorJazzberryJam, GColorFashionMagenta},
	{GColorChromeYellow, GColorYellow, GColorSpringBud},
	{GColorSunsetOrange, GColorBrightGreen, GColorVividCerulean},
	{GColorMelon, GColorPurple, GColorOrange},
	{GColorCyan, GColorRed, GColorYellow},
	{GColorElectricUltramarine, GColorOxfordBlue, GColorLiberty},
	{GColorDarkCandyAppleRed, GColorWindsorTan, GColorChromeYellow},
	{GColorYellow, GColorPastelYellow, GColorLimerick},
	{GColorCeleste, GColorBabyBlueEyes, GColorPastelYellow}
};

static void canvas_update_proc(Layer *s_canvas_layer, GContext *ctx) {
	int pal = rand() % COLOR_PALETTES;
	//int pal = COLOR_PALETTES - 1;

	int digits[4] = {
		(hour - (hour % 10))/10,
		hour % 10,
		(minute - (minute % 10))/10,
		minute % 10
	};

	int px_size = 13;

	// APP_LOG(APP_LOG_LEVEL_DEBUG,"digits: %d %d %d %d", digits[0], digits[1], digits[2], digits[3]);

	for(int i = 0; i < 11; ++i) {
		for(int j = 0; j < 13; ++j) {
			int x = (px_size * i);
			int y = (px_size * j);

			int col = rand() % COLOR_PARTS;
			GRect rect_bounds = GRect(x, y, px_size, px_size);

			graphics_context_set_fill_color(ctx, colors[pal][col]);

			graphics_draw_rect(ctx, rect_bounds);
			graphics_fill_rect(ctx, rect_bounds, 0, GCornersAll);
		}
	}

	for(int i = 0; i < 11; ++i) {
		for(int j = 0; j < 13; ++j) {
			bool draw = 1;

			int current_digit = 0;
			if(i > 0 && j < 12 && j > 0 && i < 10) {
				if(i >= 1 && i <= 4 && j <= 5) { current_digit = 0; draw = 0; }
				if(i >= 6 && i <= 9 && j <= 5) { current_digit = 1; draw = 0; }
				if(i >= 1 && i <= 4 && j >= 7) { current_digit = 2; draw = 0; }
				if(i >= 6 && i <= 9 && j >= 7) { current_digit = 3; draw = 0; }
			}

			int drawing_num = digits[current_digit];
			//APP_LOG(APP_LOG_LEVEL_DEBUG,"current_digit: %d (%d)", digits[current_digit], current_digit);

			int d_row = 0;
			int d_col = 0;
			if(!draw) {
				if(current_digit == 0) {
					d_row = i - 1;
					d_col = j - 1;
				}
				if(current_digit == 1) {
					d_row = i - 6;
					d_col = j - 1;
				}
				if(current_digit == 2) {
					d_row = i - 1;
					d_col = j - 7;
				}
				if(current_digit == 3) {
					d_row = i - 6;
					d_col = j - 7;
				}
			}

			int x = (px_size * i);
			int y = (px_size * j);

			//APP_LOG(APP_LOG_LEVEL_DEBUG,"x %d y %d", x, y);

			if(!(draw || (!draw && !numbers[drawing_num][d_col][d_row]))) {
				GRect rect_bounds = GRect(x-2, y-2, px_size+4, px_size+4);

				graphics_context_set_fill_color(ctx, GColorWhite);

				graphics_draw_rect(ctx, rect_bounds);
				graphics_fill_rect(ctx, rect_bounds, 0, GCornersAll);
			}
		}
	}

	for(int i = 0; i < 11; ++i) {
		for(int j = 0; j < 13; ++j) {
			bool draw = 1;

			int current_digit = 0;
			if(i > 0 && j < 12 && j > 0 && i < 10) {
				if(i >= 1 && i <= 4 && j <= 5) { current_digit = 0; draw = 0; }
				if(i >= 6 && i <= 9 && j <= 5) { current_digit = 1; draw = 0; }
				if(i >= 1 && i <= 4 && j >= 7) { current_digit = 2; draw = 0; }
				if(i >= 6 && i <= 9 && j >= 7) { current_digit = 3; draw = 0; }
			}

			int drawing_num = digits[current_digit];
			//APP_LOG(APP_LOG_LEVEL_DEBUG,"current_digit: %d (%d)", digits[current_digit], current_digit);

			int d_row = 0;
			int d_col = 0;
			if(!draw) {
				if(current_digit == 0) {
					d_row = i - 1;
					d_col = j - 1;
				}
				if(current_digit == 1) {
					d_row = i - 6;
					d_col = j - 1;
				}
				if(current_digit == 2) {
					d_row = i - 1;
					d_col = j - 7;
				}
				if(current_digit == 3) {
					d_row = i - 6;
					d_col = j - 7;
				}
			}

			int x = (px_size * i);
			int y = (px_size * j);

			//APP_LOG(APP_LOG_LEVEL_DEBUG,"x %d y %d", x, y);

			if(!(draw || (!draw && !numbers[drawing_num][d_col][d_row]))) {
				GRect rect_bounds = GRect(x, y, px_size, px_size);

				graphics_context_set_fill_color(ctx, GColorBlack);

				graphics_draw_rect(ctx, rect_bounds);
				graphics_fill_rect(ctx, rect_bounds, 0, GCornersAll);
			}
		}
	}
}

static Window *window;

static void main_window_load(Window *window) {
	window_set_background_color(window, GColorBlack);

	GRect bounds = layer_get_bounds(window_get_root_layer(window));
	s_canvas_layer = layer_create(bounds);
	layer_set_update_proc(s_canvas_layer, canvas_update_proc);
	layer_add_child(window_get_root_layer(window), s_canvas_layer);
}

static void main_window_unload(Window *window) {
	layer_destroy(s_canvas_layer);
}

static void update_time() {
	time_t temp = time(NULL);
	struct tm *tick_time = localtime(&temp);

	static char s_buffer[3];
	strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H" : "%I", tick_time);
	hour = atoi(s_buffer);
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "hour: %d", hour);

	strftime(s_buffer, sizeof(s_buffer), "%M", tick_time);
	minute = atoi(s_buffer);
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "minute: %d", minute);
}

bool did_init = 0;
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
	update_time();
	if(did_init) {
		layer_mark_dirty(s_canvas_layer);
	} else {
		did_init = 1;
	}
}

static void init() {
	update_time();

	window = window_create();

	window_set_window_handlers(window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload
	});

	window_stack_push(window, true);

	tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
	window_destroy(window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}