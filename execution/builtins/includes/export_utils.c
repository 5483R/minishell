#include "../builtins.h"

void    create_or_update_env_item(t_env **env, char *arg)
{
    t_env *found;
    char *key;
    char *value;

    value = NULL;
    key = extract_env_key(arg);
    if (key)
    {
        found = get_env_item_or_none(key, *env);
        if (!found)
            add_env_item(env, arg);
        else
        {
            value = extract_env_value(arg);
            update_env_value(found, value);
        }
            
    }
}