package br.edu.ifba.embarcados.drivervigilancia.mail;

import java.util.Properties;
import javax.mail.Address;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;

public class JavaMailApp
{
      public static void sendMail() {
            Properties props = new Properties();
            /** Parâmetros de conexão com servidor Gmail */
            props.put("mail.smtp.host", "smtp.gmail.com");
            props.put("mail.smtp.socketFactory.port", "465");
            props.put("mail.smtp.socketFactory.class", "javax.net.ssl.SSLSocketFactory");
            props.put("mail.smtp.auth", "true");
            props.put("mail.smtp.port", "465");

            final Senha auth = new Senha();
            Session session = Session.getDefaultInstance(props,
                        new javax.mail.Authenticator() {
                             protected PasswordAuthentication getPasswordAuthentication()
                             {
                                   return new PasswordAuthentication(auth.getEmail(), auth.getSenha());
                             }
                        });

            /** Ativa Debug para sessão */
            session.setDebug(true);

            try {

                  Message message = new MimeMessage(session);
                  message.setFrom(new InternetAddress(auth.getEmail())); //Remetente

                  Address[] toUser = InternetAddress //Destinatário(s)
                             .parse("randlersi@gmail.com, msp.ramon@gmail.com");
                  /*
                  Address[] toUser = InternetAddress //Destinatário(s)
                          .parse("randlersi@gmail.com, msp.ramon@gmail.com");  
                  */
                  message.setRecipients(Message.RecipientType.TO, toUser);
                  message.setSubject("[EMBARCADOS] Lascou!");//Assunto
                  message.setText("Atenção, você está sendo roubado.");
                  /**Método para enviar a mensagem criada*/
                  Transport.send(message);

                  System.out.println("Feito!!!");

             } catch (MessagingException e) {
                  throw new RuntimeException(e);
            }
      }
}

