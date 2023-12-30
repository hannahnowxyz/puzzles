//ignores all non-digit characters and not careful of overflow
//seeks to end of digits, then parses back
int parse_num_from_ascii(unsigned char* start_byte)
{
    int parsed_num = 0;
    int dec_fac = 1;
    int offset = 0;
    while ('0' <= start_byte[offset + 1] && start_byte[offset + 1] <= '9') offset++;
    while ('0' <= start_byte[offset] && start_byte[offset] <= '9')
    {
        parsed_num += dec_fac*(start_byte[offset] - 0x30);
        dec_fac *= 10;
        offset--;
    }
    return parsed_num;
}
