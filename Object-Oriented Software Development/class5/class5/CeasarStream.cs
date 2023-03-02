using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace class5
{
    class CeasarStream : Stream
    {
        private Stream stream;
        private int offset;

        public CeasarStream(Stream stream, int offset)
        {
            this.stream = stream;
            this.offset = offset;
        }

        public override bool CanRead => stream.CanRead;

        public override bool CanSeek => stream.CanSeek;

        public override bool CanWrite => stream.CanWrite;

        public override long Length => stream.Length;

        public override long Position { get => stream.Position; set => stream.Position = value; }

        public override void Flush()
        {
            stream.Flush();
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            int read = stream.Read(buffer, offset, count);
            for(int i = 0; i < buffer.Length; i++)
            {
                buffer[i] = (byte)((UInt16)(buffer[i] + this.offset) & ~0b11111111);
            }
            return read;
        }

        public override long Seek(long offset, SeekOrigin origin)
        {
            return stream.Seek(offset, origin);
        }

        public override void SetLength(long value)
        {
            stream.SetLength(value);
        }

        public override void Write(byte[] buffer, int offset, int count)
        {
            byte[] buffer2 = new byte[buffer.Length];
            for (int i = 0; i < buffer.Length; i++)
            {
                buffer2[i] = (byte)((UInt16)(buffer[i] + this.offset) & ~0b11111111);
            }
            stream.Write(buffer2, offset, count);
        }
    }
}
