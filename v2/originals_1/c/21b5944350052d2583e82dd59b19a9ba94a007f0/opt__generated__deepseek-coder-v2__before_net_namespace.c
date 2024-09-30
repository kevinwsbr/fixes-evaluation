struct pernet_operations my_pernet_ops = {
    .init = my_init_function,
    .exit = my_exit_function,
};

register_pernet_device(&my_pernet_ops);
// Use the network namespace operations as needed
unregister_pernet_device(&my_pernet_ops);
