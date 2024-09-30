**Event Management Tasks**

| Task | Command |
|---|---|
| Publish Event | `MISP/app/Console/cake Event publish [event_id] [pass_along] [job_id] [user_id]` |
| Publish Sightings | `MISP/app/Console/cake Event publish_sightings [event_id] [pass_along] [job_id] [user_id]` |
| Publish Galaxy Clusters | `MISP/app/Console/cake Event publish_galaxy_clusters [cluster_id] [job_id] [user_id] [pass_along]` |
| Cache Event | `MISP/app/Console/cake Event cache [user_id] [event_id] [export_type]` |
| Cache Bro | `MISP/app/Console/cake Event cachebro [user_id] [event_id]` |
| Recover Event | `MISP/app/Console/cake Event recoverEvent [job_id] [event_id]` |
| Alert Email | `MISP/app/Console/cake Event alertemail [user_id] [job_id] [event_id] [old_publish]` |
| Contact Email | `MISP/app/Console/cake Event contactemail [event_id] [message] [all] [user_id] [process_id]` |
| Posts Email | `MISP/app/Console/cake Event postsemail [user_id] [post_id] [event_id] [title] [message] [process_id]` |
| Enqueue Caching | `MISP/app/Console/cake Event enqueueCaching [timestamp]` |
| Do Publish | `MISP/app/Console/cake Event doPublish [event_id]` |
| Run Enrichment | `MISP/app/Console/cake Event enrichment [user_id] [event_id] [json_encoded_module_list]` |
| Process Free Text | `MISP/app/Console/cake Event processfreetext [input]` |
| Process Module Result | `MISP/app/Console/cake Event processmoduleresult [input]` |

**Worker Management Tasks**

| Task | Command |
|---|---|
| Get List of Workers | `MISP/app/Console/cake Admin getWorkers [all|dead]` |
| Start a Worker | `MISP/app/Console/cake Admin startWorker [queue_name]` |
| Restart a Worker | `MISP/app/Console/cake Admin restartWorker [worker_pid]` |
| Restart All Workers | `MISP/app/Console/cake Admin restartWorkers` |
| Kill a Worker | `MISP/app/Console/cake Admin killWorker [worker_pid]` |