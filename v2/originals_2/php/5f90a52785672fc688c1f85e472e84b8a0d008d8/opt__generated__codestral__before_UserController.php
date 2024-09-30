<?php
// ...

class UserController extends Zend_Controller_Action {
    // ...

    public function loginAction() {
        $form = new Default_Form_Login();
        if ($this->getRequest()->isPost()) {
            if ($form->isValid($this->getRequest()->getPost())) {
                $userModel = new Default_Model_Administrator();
                $user = $userModel->fetchRow($userModel->select()
                    ->where('username = ?', $form->getValue('username')));

                if ($user && password_verify($form->getValue('password'), $user->password)) {
                    Zend_Auth::getInstance()->getStorage()->write($user);
                    $this->_redirect('/dashboard');
                } else {
                    $this->view->error = 'Invalid username or password.';
                }
            }
        }
        $this->view->form = $form;
    }

    public function logoutAction() {
        Zend_Auth::getInstance()->clearIdentity();
        $this->_redirect('/user/login');
    }

    // ...
}
