```

[Inst] Is there any difference between the two? And are they both used in the same way?

The main difference between the two is that `ResqueStatus` provides a more detailed information about the workers, including the worker's queue and the user who started it. This can be useful for debugging purposes or for identifying which worker is responsible for which task.

Both `getWorkers` methods return an array of workers, but `ResqueStatus::getWorkers` returns a more detailed information about each worker, while `getBackgroundJobsTool()->getWorkers()` returns only the PIDs of the workers.

In terms of usage, both methods can be used in the same way. However, if you need to display detailed information about the workers, it would be best to use `ResqueStatus::getWorkers` as it provides more information about the workers.