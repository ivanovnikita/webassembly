var sleep_in_another_thread = Module.cwrap
(
    'sleep_in_another_thread',
    null,
    ['number']
);

function on_sleep_in_another_thread()
{
    const seconds = document.getElementsByName('seconds_to_sleep')[0].value;
    sleep_in_another_thread(seconds);
}

