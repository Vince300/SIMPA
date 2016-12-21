int is_big_endian() {

    /* Are we little or big endian?  From Harbison&Steele.  */
    union
            {
            long l;
            char c[sizeof (long)];
            } u ;

    u.l = 1 ;
    return (u.c[sizeof (long) - 1] == 1) ;
}

int main() {

    return is_big_endian() ;
}

