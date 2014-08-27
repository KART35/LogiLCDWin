#include "PNGHandler.h"
#include <iostream>
#include <stdio.h>




PNGHandler::PNGHandler(LogiLCD * in)
{
	
	this->lcd = in;
}

bool PNGHandler::saveImage(char* file_name)
{
	x = 0;
	y = 0;
	FILE *fp = NULL;
	fopen_s( &fp, file_name, "wb");
	if (!fp)
		return false;
	png_ptr = png_create_write_struct
		(
		PNG_LIBPNG_VER_STRING,
		NULL,
		NULL,
		NULL
		);
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		png_destroy_write_struct(&png_ptr, NULL);
		return false;
	}
	png_init_io(png_ptr, fp);
	png_set_IHDR(
		png_ptr,
		info_ptr,
		width,
		height,
		bit_depth,
		color_type,
		PNG_INTERLACE_ADAM7,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_BASE
		);
	
	png_write_info(png_ptr, info_ptr);
	png_set_packing(png_ptr);
	png_byte ** row_pointers = NULL;
	row_pointers = (png_bytep*)png_malloc(png_ptr, height * sizeof (png_byte *));
	for (y = 0; y < height; ++y) {
		png_byte* row = (png_byte*)png_malloc(png_ptr, sizeof (png_byte)* width * 3);
		row_pointers[y] = row;
		for (x = 0; x < width; ++x) {
			
			*row++ = this->lcd->page[(y*width)+x][LogiLCD::pix::r];
			*row++ = this->lcd->page[(y*width) + x][LogiLCD::pix::g];
			*row++ = this->lcd->page[(y*width) + x][LogiLCD::pix::b];
		}
	}
	png_set_rows(png_ptr, info_ptr, row_pointers);
	//png_write_end(png_ptr, NULL);
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
	fclose(fp);
	return true;
}
