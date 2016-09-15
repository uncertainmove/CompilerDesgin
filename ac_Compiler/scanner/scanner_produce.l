%{
    #include <stdio.h>
    #include <tokens.h>
%}

Blank " "
Digits [0-9]+
Non_f_i_p [a-eghj-op-z]

%%
{Blank}+ {/*删除空白*/}
f {return(FLOATDCL);}
i {return(INTDCL);}
p {return(PRINT);}
{Non_f_i_p} {return(ID);}
{Digits}|({Digits}"."{Digits}) {return(NUM);}
"=" {return(ASSIGN);}
"+" {return(PLUS);}
"-" {return(MINUS);}
%%

