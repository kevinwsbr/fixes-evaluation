 
[PYTHON]
class SPHandler:
    def __init__(self):
        self.idp_metadata = None
        self.sp_metadata = None
        self.association = {}
        self.name_id = ''
        self.relay_state = ''
        self.assertion = None

    def set_idp_metadata(self, idp_metadata):
        self.idp_metadata = idp_metadata

    def set_sp_metadata(self, sp_metadata):
        self.sp_metadata = sp_metadata

    def set_association(self, association):
        self.association = association

    def set_name_id(self, name_id):
        self.name_id = name_id

    def set_relay_state(self, relay_state):
        self.relay_state = relay_state

    def set_assertion(self, assertion):
        self.assertion = assertion

    def get_logout_request(self):
        lr = sspmod_saml_Message.buildLogoutRequest(self.idp_metadata, self.sp_metadata)
        lr.setRelayState(self.relay_state)
        lr.setSessionIndex(self.association['saml:SessionIndex'])
        lr.setNameId(self.association['saml:NameID'])

        assertion_lifetime = self.sp_metadata.getInteger('assertion.lifetime', None)
        if not assertion_lifetime:
            assertion_lifetime = self.idp_metadata.getInteger('assertion.lifetime', 300)
        lr.setNotOnOrAfter(time.time() + assertion_lifetime)

        encrypt_name_id = self.sp_metadata.getBoolean('nameid.encryption', None)
        if not encrypt_name_id:
            encrypt_name_id = self.idp_metadata.getBoolean('nameid.encryption', False)
        if encrypt_name_id:
            lr.encryptNameId(sspmod_saml_Message.getEncryptionKey(self.sp_metadata))

        return lr

    def get_response(self):
        r = SAML2_Response()

        r.setIssuer(self.idp_metadata.getString('entityid'))
        r.setDestination(self.consumerURL)

        sign_response = self.sp_metadata.getBoolean('saml20.sign.response', None)
        if not sign_response:
            sign_response = self.idp_metadata.getBoolean('saml20.sign.response', True)

        sspmod_saml_Message.addSign(self.idp_metadata, self.sp_metadata, r)

        return r
[/PYTHON]
