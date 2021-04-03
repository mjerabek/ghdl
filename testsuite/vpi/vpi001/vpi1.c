#include <stdio.h>
#include <vpi_user.h>
#define N_NAMES 12

void
vpi_proc (void)
{
  vpiHandle net;
  s_vpi_value val;
  char names[N_NAMES][64] =
    {
     // Integers
     "myentity.sigint",
     "myentity.iportint",
     "myentity.genint",
     "myentity.constint",

     // Std_logic
     "myentity.sigsl",
     "myentity.iportsl",
     "myentity.gensl",
     "myentity.constsl",

     // Boolean
     "myentity.sigbool",
     "myentity.iportbool",
     "myentity.genbool",
     "myentity.constbool",

     // String
     //"myentity.genstring", -- Not supported
     //"myentity.conststring" -- Not supported
    };
                       
  for (int name_index=0; name_index<N_NAMES; name_index+=1) {
    printf ("Trying to find name %s\n", names[name_index]);
    net = vpi_handle_by_name (names[name_index], NULL);
    if (net == NULL)
        {
        printf ("Error: Failed to find the net %s\n", names[name_index]);
        return;
        }
    val.format = vpiBinStrVal;
    vpi_get_value (net, &val);
    printf ("value: %s\n", val.value.str);
  }
}

void my_handle_register()
{
  s_cb_data cb;
  printf ("Hello world\n");

  cb.reason = cbEndOfCompile;
  cb.cb_rtn = &vpi_proc;
  cb.user_data = NULL;
  if (vpi_register_cb (&cb) == NULL)
    vpi_printf ("Error: Cannot register EndOfCompile call back\n");
}

void (*vlog_startup_routines[]) () =
{
  my_handle_register,
  0
};
