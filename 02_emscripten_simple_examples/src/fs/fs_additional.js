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

function on_from_virtual_fs_to_disk()
{
    const filepath = document.getElementsByName('name_of_file_to_download')[0].value;
    const path_parts = filepath.split('/');
    const filename = path_parts[path_parts.length - 1];
    const file_content = FS.readFile(filepath, { encoding: 'binary' });
    var tmp_download_element = document.createElement("a");
    tmp_download_element.href = window.URL.createObjectURL(new Blob([file_content]));
    tmp_download_element.download = filename;
    tmp_download_element.click();
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
