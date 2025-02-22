        ��  ��                  (      �� ��     0 	           A  A     D  V  �  �  Displays or modifies access control lists (ACLs) of files

CACLS filename [/T] [/E] [/C] [/G user:perm] [/R user [...]]
               [/P user:perm [...]] [/D user [...]]
   filename      Displays ACLs.
   /T            Changes ACLs of specified files in
                 the current directory and all subdirectories.
   /E            Edit ACL instead of replacing it.
   /C            Continue on access denied errors.
   /G user:perm  Grant specified user access rights.
                 Perm can be: R  Read
                              W  Write
                              C  Change (write)
                              F  Full control
   /R user	 Revoke specified user's access rights (only valid with /E).
   /P user:perm  Replace specified user's access rights.
                 Perm can be: N  None
                              R  Read
                              W  Write
                              C  Change (write)
                              F  Full control
   /D user       Deny specified user access.
Wildcards can be used to specify more that one file in a command.
You can specify more than one user in a command.
     ACCESS_DENIED%0
     Are you sure (Y/N)?%0
    processed dir: %0
    processed file: %0
        <User Name not found>%0
   $    <Account Domain not found>%0
    (OI)%0
       (CI)%0
       (NP)%0
       (IO)%0
       (DENY)%0
     (special access:)
    N%0
      R%0
      C%0
      F%0
      Y%0
      YES%0
     SHARING_VIOLATION%0
  