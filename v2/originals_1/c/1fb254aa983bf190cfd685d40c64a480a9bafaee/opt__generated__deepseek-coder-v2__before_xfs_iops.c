   struct inode *inode = &ip->i_vnode;
   inode->i_ino = ip->i_ino;
   inode->i_state = I_NEW;
   