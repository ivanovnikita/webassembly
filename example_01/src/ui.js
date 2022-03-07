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

var get_allocated_message = Module.cwrap
(
    'get_allocated_message',
    'number'
);

function on_click_get_allocated_message()
{
    const message_ptr = get_allocated_message();
    const message = Module.UTF8ToString(message_ptr); 

    Module._free(message_ptr);

    console.log(message);
}

var invoke_assert = Module.cwrap
(
    'invoke_assert',
    null,
);

function on_invoke_assert()
{
    invoke_assert();
}

var throw_exception = Module.cwrap
(
    'throw_exception',
    null,
);

function on_throw_exception()
{
    throw_exception();
}

var write_to_file = Module.cwrap
(
    'write_to_file',
    null,
    ['string', 'string']
);

function on_write_to_file()
{
    const filename = document.getElementsByName('name_of_file_to_write')[0].value;
    const message = document.getElementsByName('text_to_write')[0].value;
    write_to_file(filename, message);
}

var read_from_file = Module.cwrap
(
    'read_from_file',
    null,
    ['string']
);

function on_read_from_file()
{
    const filename = document.getElementsByName('name_of_file_to_read')[0].value;
    read_from_file(filename);
}

function on_from_disk_to_virtual_fs()
{
    const file = document.getElementById("choose_file").files[0];
    if (file)
    {
        var reader = new FileReader();

        reader.onload = function (evt)
        {
            const data = new Uint8Array(evt.target.result);
            const filename = document.getElementsByName('name_of_virtual_file_to_write')[0].value;
            FS.writeFile(filename, data, { flags: 'w+', encoding: 'binary' });
        };

        reader.onerror = function (evt)
        {
            console.error("An error ocurred reading the file", evt);
        };

        reader.readAsArrayBuffer(file);
    }
}

function on_mount_persistent_fs()
{
    const mount_point = document.getElementsByName('mount_point')[0].value;
    FS.mkdir(mount_point);
    FS.mount(IDBFS, {}, mount_point);
}

function on_restore_from_idbfs()
{
    FS.syncfs
    (
        true,
        function (err)
        {
            console.log('Persistent FS restored');
        }
    );
}

function on_save_to_idbfs()
{
    FS.syncfs
    (
        false,
        function (err)
        {
            console.log('Persistent FS saved');
        }
    );
}
