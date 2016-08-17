#include <time.h>
#include <stdlib.h>
#include <pebble.h>
#include <math.h>

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

#define COLOR_PALETTES 27
#define COLOR_PARTS 3
GColor colors[][COLOR_PARTS] = {
	{GColorBlack, GColorVividCerulean, GColorElectricBlue},
	{GColorIndigo, GColorVividCerulean, GColorElectricBlue},
	{GColorJaegerGreen, GColorDarkGreen, GColorBlack},
	{GColorYellow, GColorFashionMagenta, GColorLavenderIndigo},
	{GColorChromeYellow, GColorYellow, GColorWindsorTan},
	{GColorRed, GColorImperialPurple, GColorBlue},
	{GColorDarkCandyAppleRed, GColorWindsorTan, GColorChromeYellow},
	{GColorOxfordBlue, GColorElectricUltramarine, GColorLiberty},
	{GColorPurple, GColorOrange, GColorMelon},
	{GColorVividCerulean, GColorSunsetOrange, GColorBrightGreen},
	{GColorOxfordBlue, GColorJazzberryJam, GColorFashionMagenta},
	{GColorLightGray, GColorDarkGray, GColorBlack},
	{GColorMidnightGreen, GColorCadetBlue, GColorCyan},
	{GColorImperialPurple, GColorPurple, GColorMagenta},
	{GColorOxfordBlue, GColorDukeBlue, GColorBlueMoon},
	{GColorBulgarianRose, GColorDarkCandyAppleRed, GColorRed},
	{GColorMagenta, GColorBrilliantRose, GColorRichBrilliantLavender},
	{GColorIndigo, GColorPurple, GColorPurpureus},
	{GColorBlue, GColorBlueMoon, GColorVividCerulean},
	{GColorCyan, GColorVividCerulean, GColorBlueMoon},
	{GColorElectricBlue, GColorCyan, GColorCeleste},
	{GColorGreen, GColorIslamicGreen, GColorDarkGreen},
	{GColorGreen, GColorScreaminGreen, GColorSpringBud},
	{GColorOrange, GColorRajah, GColorYellow},
	{GColorRed, GColorSunsetOrange, GColorMelon},
	{GColorDarkGray, GColorLightGray, GColorWhite},
	{GColorRajah, GColorJaegerGreen, GColorDarkGreen},
};

bool is_dark[] = {
	1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0
};

void draw_custom_pixel(GContext *ctx, int x, int y, int px_size, GColor color) {
	int pos = x/px_size;
	GRect rect_bounds = GRect(x, y, (pos >= 10 ? px_size+1 : px_size), px_size);
	//GRect rect_bounds = GRect(x, y, px_size, px_size);

	graphics_context_set_fill_color(ctx, color);

	graphics_draw_rect(ctx, rect_bounds);
	graphics_fill_rect(ctx, rect_bounds, 0, GCornerNone);
}

static void canvas_update_proc(Layer *s_canvas_layer, GContext *ctx) {
	srand(time(NULL) - (time(NULL) % 60));

	//int pal = 0;
	int pal = rand() % COLOR_PALETTES;
	//int pal = COLOR_PALETTES - 1;
	//int pal = 33;

	int digits[4] = {
		(hour - (hour % 10))/10,
		hour % 10,
		(minute - (minute % 10))/10,
		minute % 10
	};

	int screen_width = 11;
	int screen_height = 13;
	int px_size = 13;

	// APP_LOG(APP_LOG_LEVEL_DEBUG,"digits: %d %d %d %d", digits[0], digits[1], digits[2], digits[3]);

	// +2 on width/height respectively, can't be variables here
	short grid[13][15] = { 0 };

	for(int i = 0; i < screen_width+2; ++i) {
		for(int j = 0; j < screen_height+2; ++j) {
			grid[i][j] = rand() % 2;
		}
	}

	for(int i = 1; i < screen_width+1; ++i) {
		for(int j = 1; j < screen_height+1; ++j) {
			int x = (px_size * (i-1));
			int y = (px_size * (j-1));

			int col = grid[i][j];
			col = col + grid[i+1][j];
			col = col + grid[i-1][j];
			col = col + grid[i][j+1];
			col = col + grid[i][j-1];

			col = col - 1;

			if(col <= 0) {
				col = 0;
			}
			if(col > 2) {
				col = 2;
			}

			if(rand() % 2 == 1) {
				col = (col - 2) * -1;
			}

			draw_custom_pixel(ctx, x, y, px_size, colors[pal][col]);
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
				switch(current_digit) {
					case 0:
						d_row = i - 1;
						d_col = j - 1;
						break;

					case 1:
						d_row = i - 6;
						d_col = j - 1;
						break;

					case 2:
						d_row = i - 1;
						d_col = j - 7;
						break;

					case 3:
						d_row = i - 6;
						d_col = j - 7;
						break;
				}
			}

			int x = (px_size * i);
			int y = (px_size * j);

			//APP_LOG(APP_LOG_LEVEL_DEBUG,"x %d y %d", x, y);

			if(!(draw || (!draw && !numbers[drawing_num][d_col][d_row]))) {
				draw_custom_pixel(ctx, x-3, y-3, px_size+6, is_dark[pal] ? GColorBlack : GColorWhite);
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
				switch(current_digit) {
					case 0:
						d_row = i - 1;
						d_col = j - 1;
						break;

					case 1:
						d_row = i - 6;
						d_col = j - 1;
						break;

					case 2:
						d_row = i - 1;
						d_col = j - 7;
						break;

					case 3:
						d_row = i - 6;
						d_col = j - 7;
						break;
				}
			}

			int x = (px_size * i);
			int y = (px_size * j);

			//APP_LOG(APP_LOG_LEVEL_DEBUG,"x %d y %d", x, y);

			if(!(draw || (!draw && !numbers[drawing_num][d_col][d_row]))) {
				draw_custom_pixel(ctx, x, y, px_size, is_dark[pal] ? GColorWhite : GColorBlack);
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