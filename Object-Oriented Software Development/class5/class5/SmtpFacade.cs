using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Mail;
using System.Text;
using System.Threading.Tasks;

namespace class5
{
    class SmtpFacade
    {
        public void SendTo(string From, string To, string Subject, 
                           string Body, Stream Attachment, string AttachmentMimeType)
        {
            MailMessage msg = new MailMessage(From, To, Subject, Body);
            if(Attachment != null)
            {
                msg.Attachments.Add(new Attachment(Attachment, AttachmentMimeType));
            }
            new SmtpClient().Send(msg);
        }
    }
}
