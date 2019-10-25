#define protected_act(stack_act)                  \
    err_code = stack_act;                        \
    if (err_code != 0)                            \
    {                                             \
        processor.diagnostic (err_code);          \
        printf("Number of wrong string:%d", i/2+1); \
        abort();                                  \
    }

DEF_CMD (PUSH, 1, 1,
{
    protected_act ( processor.push(code[i+1]) );
})

DEF_CMD (ADD, 2, 0,
{
	int a = 0;
	int b = 0;
	protected_act ( processor.pop (a) );
	protected_act ( processor.pop (b) );
	protected_act ( processor.push (a + b) );
})

DEF_CMD (SUB, 3, 0,
{
	int a = 0;
	int b = 0;
	protected_act ( processor.pop(a) );
	protected_act ( processor.pop(b) );
	protected_act ( processor.push(a - b) );
})

DEF_CMD(MUL, 4, 0,
{
	int a = 0;
	int b = 0;
	protected_act ( processor.pop(a) );
	protected_act ( processor.pop(b) );
	protected_act ( processor.push( (a * b)/100) );
})

DEF_CMD(DIV, 5, 0,
{
	int a = 0;
	int b = 0;
	protected_act ( processor.pop(a) );
	protected_act ( processor.pop(b) );
	protected_act ( processor.push( (a / b)*100) );
})

DEF_CMD(SQRT, 9, 0,
{
	int a = 0;
	float b = ((float)a)/100;
	protected_act ( processor.pop (a) );
	b /= 100;
	b = sqrt(b);
	a = b * 100;
	protected_act ( processor.push(a) );
})

DEF_CMD(IN, 10, 0,
{
	float a = 0;
	printf ("Print a value to PUSH: ");
	scanf ("%f", &a);
	protected_act ( processor.push(a*100) );
})

DEF_CMD(OUT, 11, 0,
{
	int a = 0;
	protected_act ( processor.pop (a) );
	printf ("Programm print: %d.%d\n", a/100, a%100);
})

DEF_CMD (PUSH _X, 100, 2,
{
    protected_act ( processor.push(r [ code [i+1]/100 ] ) );
})

DEF_CMD (POP _X, 200, 2,
{
    protected_act ( processor.pop (r [ code [i+1]/100 ] ) );
})


DEF_CMD (JMP, 210, 1,
{
    i = code[i+1]/100 - 2;
})

DEF_CMD (END, 255, 0,
{
    goto end;
})
