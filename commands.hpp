#define protected_act(stack_act)             \
    err_code = stack_act ;                           \
    if (err_code != 0)                                   \
    {                                                              \
        processor.diagnostic (err_code);      \
        abort();                                               \
    }

DEF_CMD (PUSH, 1,
{
    protected_act ( processor.push(code[i+1]) );
})

DEF_CMD (ADD, 2,
{
	int a = 0;
	int b = 0;
	protected_act ( processor.pop (a) );
	protected_act ( processor.pop (b) );
	protected_act ( processor.push (a + b) );
})

DEF_CMD (SUB, 3,
{
	int a = 0;
	int b = 0;
	protected_act ( processor.pop(a) );
	protected_act ( processor.pop(b) );
	protected_act ( processor.push(a - b) );
})

DEF_CMD(MUL, 4,
{
	int a = 0;
	int b = 0;
	protected_act ( processor.pop(a) );
	protected_act ( processor.pop(b) );
	protected_act ( processor.push(a * b));
})

DEF_CMD(DIV, 5,
{
	int a = 0;
	int b = 0;
	protected_act ( processor.pop(a) );
	protected_act ( processor.pop(b) );
	protected_act ( processor.push(a / b) );
})
