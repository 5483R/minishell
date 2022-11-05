#include "../builtins.h"



// append or overwrite

/*

export ab+=text ---> create or update (key = ab, value = text)

ab = 2;
if export ab+=[value] ----> add [value]
if export ab=[value]  ----> overwrite with [value]

if '=' or '+=' not found in arg, and key is valid, then value ===> NULL;

if arg start with something different then (a-z, A-Z, '_') before '=' or '+=' 
                        then arg is not valid;

*/


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