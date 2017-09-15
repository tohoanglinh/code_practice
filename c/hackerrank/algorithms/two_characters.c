/* Two Characters
 * String t always consists of two distinct alternating characteres. For example,
 * if string t's two distinct characters are x and y, then t could be xyxyx or yxyxy
 * but not xxyy or xyyx.
 * You can convert some string s to string t by deleting characters from s. When you
 * delete a character from s, you must delete all occurences of it in s. For example,
 * if s = abaacdabd, and you delete the character a, then the string become bcdbd.
 * Given s, convert it to the longest possible string t. Then print the length of
 * string t on a new line; if no string t can be formed from s, print 0 instead.
 */

#include <stdio.h>

int main(void)
{
    /* s_len: length of s */
    int s_len;
    scanf("%d", &s_len);

    char *s;
    s = malloc(s_len*sizeof(char));
    if (NULL == s)
    {
        return (-1);
    }
    

    
    free(s);
    return 0;
}
