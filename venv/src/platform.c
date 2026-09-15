#include "platform.h"

#include "process_spawner.h"

int venv_spawn_in_venv(const venv_config *cfg, const venv_command *command,
                       int *exit_code, char *err, size_t errlen)
{
    return venv_process_spawner_run(cfg, command, exit_code, err, errlen);
}
