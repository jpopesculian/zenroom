-- Zencode data schemas for validation

schemas = {

   -- packets encoded with AES GCM
   aes_gcm = S.record {
      checksum = S.hex,
      iv = S.hex,
      schema = S.Optional(S.string),
      text = S.hex,
      zenroom = S.Optional(S.string),
      encoding = S.string,
      curve = S.string,
      pubkey = S.ecp
   },

   -- zencode_keypair
   keypair = S.record {
      schema = S.Optional(S.string),
      private = S.Optional(S.hex),
      public = S.ecp
   },

   -- zencode_ecqv
   certificate = S.record {
      schema = S.Optional(S.string),
      private = S.Optional(S.big),
      public = S.ecp,
      hash = S.big,
      from = S.string,
      authkey = S.ecp
   },

   certificate_hash = S.Record {
      schema = S.Optional(S.string),
      public = S.ecp,
      requester = S.string,
      statement = S.string,
      certifier = S.string
   },

   declaration = S.record {
      schema = S.Optional(S.string),
      from = S.string,
      to = S.string,
      statement = S.string,
      public = S.ecp
   },

   declaration_keypair = S.record {
      schema = S.Optional(S.string),
      requester = S.string,
      statement = S.string,
      public = S.ecp,
      private = S.hex
   },

   -- zencode_coconut
   coconut_ca_vk = S.record {
      g2 = S.hex,
      alpha = S.hex,
      beta = S.hex
   },
   coconut_ca_sk = S.record {
      x = S.int,
      y = S.int
   },
   coconut_ca_keypair = S.record {
      schema = S.Optional(S.string),
      version = S.Optional(S.string),
      verify = S.table,
      sign = S.table
   },

   coconut_req_keypair = S.record {
      schema = S.Optional(S.string),
      version = S.Optional(S.string),
      public = S.ecp,
      private = S.hex
   },

   coconut_pi_s = S.record {
	  rr = S.int,
	  rm = S.int,
	  rk = S.int,
	  c = S.int
   },

   coconut_pi_v = S.record {
	  rr = S.int,
	  rm = S.int,
	  c = S.int
   },

   coconut_sigmatilde = S.record {
      schema = S.Optional(S.string),
      version = S.Optional(S.string),
      h = S.ecp,
      b_tilde = S.ecp,
      a_tilde = S.ecp
   },

   coconut_sigmaprime = S.record {
	  h_prime = S.ecp,
	  s_prime = S.ecp
   },

   coconut_aggsigma = S.record {
	  schema = S.Optional(S.string),
	  version = S.Optional(S.string),
	  h = S.ecp,
	  s = S.ecp
   },

}

_G['schemas'] = schemas