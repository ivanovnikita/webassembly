var print_message = Module.cwrap
(
    'print_message', // name of C function
    null, // return type
    // argument types are omitted
);  

function on_click_print_message()
{
    print_message();
}

var get_static_message = Module.cwrap
(
    'get_static_message',
    'string' // implicitly converts 'char*' to js string using UTF8ToString
)

function on_click_get_static_message()
{
    message = get_static_message();
    console.log(message);
}

var copy_message = Module.cwrap
(
    'copy_message',
    'number',
    ['number', 'number'] // char* is not a 'string' type, it is a 'number' type
);

function on_click_copy_message()
{
    const max_message_size = 256;
    const message_buffer_ptr = Module._malloc(max_message_size);

    const message_size = copy_message(message_buffer_ptr, max_message_size);
    const message = Module.UTF8ToString(message_buffer_ptr, max_message_size); 

    Module._free(message_buffer_ptr);

    console.log(message);
}

function on_click_copy_message_direct_call()
{
    const max_message_size = 256;
    const message_buffer_ptr = _malloc(max_message_size);

    const message_size = _copy_message(message_buffer_ptr, max_message_size);
    const message = Module.UTF8ToString(message_buffer_ptr, max_message_size);

    _free(message_buffer_ptr);

    console.log(message);
}

function on_click_get_allocated_message()
{
    const message_ptr = _get_allocated_message();
    const message = Module.UTF8ToString(message_ptr); 

    _free(message_ptr);

    console.log(message);
}

function on_call_js_caller()
{
    _call_js();
}

function on_invoke_assert()
{
    _invoke_assert();
}

function on_throw_exception()
{
    _throw_exception();
}
