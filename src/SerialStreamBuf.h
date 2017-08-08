/******************************************************************************
 *   @file SerialStreamBuf.h                                                  *
 *   @copyright                                                               *
 *                                                                            *
 *   This program is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by     *
 *   the Free Software Foundation; either version 2 of the License, or        *
 *   (at your option) any later version.                                      *
 *                                                                            *
 *   This program is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU General Public License for more details.                             *
 *                                                                            *
 *   You should have received a copy of the GNU General Public License        *
 *   along with this program; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                          *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                *
 *****************************************************************************/

#ifndef _SerialStreamBuf_h_
#define _SerialStreamBuf_h_

#include "SerialPortConstants.h"
#include <memory>

namespace LibSerial
{
    /**
     * @brief This is the streambuf subclass used by SerialStream. This
     *        subclass takes care of opening the serial port file in the
     *        required modes and providing the corresponding file
     *        descriptor to SerialStream so that various parameters
     *        associated with the serial port can be set. Several
     *        features of this streambuf class resemble those of
     *        std::filebuf, however this class it not made a subclass of
     *        filebuf because we need access to the file descriptor
     *        associated with the serial port and the standard filebuf
     *        does not provide access to it.
     *
     *        At present, this class uses unbuffered I/O and all calls
     *        to setbuf() will be ignored.
     */
    class SerialStreamBuf : public std::streambuf
    {
    public:

        /**
         * @brief Default Constructor.
         */
        explicit SerialStreamBuf();

        /**
         * @brief Constructor that allows a SerialPort instance to be 
         *        created and also initialize the corresponding serial
         *        port with the specified parameters.
         * @param fileName The file descriptor of the serial stream object.
         * @param baudRate The communications baud rate.
         * @param characterSize The size of the character buffer for
         *        storing read/write streams.
         * @param parityType The parity type for the serial stream object.
         * @param numberOfStopBits The number of stop bits.
         * @param flowControlType Flow control for the serial data stream.
         */
        explicit SerialStreamBuf(const std::string&   fileName,
                                 const BaudRate&      baudRate        = BaudRate::BAUD_DEFAULT,
                                 const CharacterSize& characterSize   = CharacterSize::CHAR_SIZE_DEFAULT,
                                 const FlowControl&   flowControlType = FlowControl::FLOW_CONTROL_DEFAULT,
                                 const Parity&        parityType      = Parity::PARITY_DEFAULT,
                                 const StopBits&      stopBits        = StopBits::STOP_BITS_DEFAULT);

        /**
         *  @brief Default Destructor.
         */
        virtual ~SerialStreamBuf();

        /**
         * @brief Opens the serial port associated with the specified
         *        fileName, and the specified mode, openMode.
         * @param fileName The file descriptor of the serial stream object.
         * @param openMode The communication mode status when the serial
         *        communication port is opened.
         */
        void Open(const std::string& filename,
                  std::ios_base::openmode openMode = std::ios_base::in | std::ios_base::out);

        /**
         * @brief Closes the serial port. All settings of the serial port will be
         *        lost and no more I/O can be performed on the serial port.
         */
        void Close();

        /**
         * @brief Flushes the serial port input buffer.
         */
        void FlushInputBuffer();

        /**
         * @brief Flushes the serial port output buffer.
         */
        void FlushOutputBuffer();

        /**
         * @brief Flushes the serial port input and output buffers.
         */
        void FlushIOBuffers();

        /**
         * @brief Checks if data is available at the input of the serial port.
         * @return Returns true iff data is available to read.
         */
        bool IsDataAvailable();

        /**
         * @brief Determines if the serial port is open for I/O.
         * @return Returns true iff the serial port is open.
         */
        bool IsOpen();

        /**
         * @brief Sets all serial port paramters to their default values.
         */
        void SetDefaultSerialPortParameters();

        /**
         * @brief Sets the baud rate for the serial port to the specified value
         * @param baudRate The baud rate to be set for the serial port.
         */
        void SetBaudRate(const BaudRate& baudRate);

        /**
         * @brief Gets the current baud rate for the serial port.
         * @return Returns the baud rate.
         */
        BaudRate GetBaudRate();

        /**
         * @brief Sets the character size for the serial port.
         * @param characterSize The character size to be set.
         */ 
        void SetCharacterSize(const CharacterSize& characterSize);

        /**
         * @brief Gets the character size being used for serial communication.
         * @return Returns the current character size. 
         */
        CharacterSize GetCharacterSize();

        /**
         * @brief Sets flow control for the serial port.
         * @param flowControl The flow control type to be set.
         */
        void SetFlowControl(const FlowControl& flowControl);

        /**
         * @brief Get the current flow control setting.
         * @return Returns the flow control type of the serial port.
         */
        FlowControl GetFlowControl();

        /**
         * @brief Sets the parity type for the serial port.
         * @param parityType The parity type to be set.
         */
        void SetParity(const Parity& parityType);

        /**
         * @brief Gets the parity type for the serial port.
         * @return Returns the parity type.
         */
        Parity GetParity();

        /**
         * @brief Sets the number of stop bits to be used with the serial port.
         * @param numberOfStopBits The number of stop bits to set.
         */
        void SetNumberOfStopBits(const StopBits& numberOfStopBits);

        /**
         * @brief Gets the number of stop bits currently being used by the serial
         * @return Returns the number of stop bits.
         */
        StopBits GetNumberOfStopBits();

        /**
         * @brief Sets the minimum number of characters for non-canonical reads.
         * @param vMin the number of minimum characters to be set.
         */
        void SetVMin(const short vmin);

        /**
         * @brief Gets the VMIN value for the device, which represents the
         *        minimum number of characters for non-canonical reads.
         * @return Returns the minimum number of characters for
         *         non-canonical reads.
         */
        short GetVMin();

        /** 
         * @brief Sets character buffer timeout for non-canonical reads in deciseconds.
         * @param vtime The timeout value in deciseconds to be set.
         */
        void SetVTime(const short vtime);

        /** 
         * @brief Gets the current timeout value for non-canonical reads in deciseconds.
         * @return Returns the character buffer timeout for non-canonical reads in deciseconds.
         */
        short GetVTime();

        /**
         * @brief Gets the serial port file descriptor.
         */
        int GetFileDescriptor();


    protected:

        /**
         * @brief Performs an operation that is defined separately for each
         *        class derived from streambuf. The default behavior is to
         *        do nothing if gptr() is non-null and gptr()!=egptr().
         *        Also, setbuf(0, 0) usually means unbuffered I/O and
         *        setbuf(p, n) means use p[0]...p[n-1] to hold the buffered
         *        characters. In general, this method implements the
         *        subclass's notion of getting memory for the buffered
         *        characters. 
         *
         *        In the case of SerialStreamBuffer, we want to keep using
         *        unbuffered I/O. Hence, using this method has no effect at
         *        present.
         */
        virtual std::streambuf* setbuf(char_type*, 
                                       std::streamsize) override;

        /**
         * @brief Writes up to n characters from the character sequence at 
         *        char s to the serial port associated with the buffer.
         * @param character Pointer to the character buffer to write to the serial port.
         * @param numberOfBytes The number of characters to write to the serial port.
         * @return Returns the number of characters that were successfully
         *         written to the serial port. 
         */
        virtual std::streamsize xsputn(const char_type* character, 
                                       std::streamsize numberOfBytes) override;
           
        /**
         * @brief Reads up to n characters from the serial port and returns
         *        them through the character array located at s.
         * @param character Pointer to the character buffer to write to the serial port.
         * @param numberOfBytes The number of characters to write to the serial port.
         * @return Returns the number of characters actually read from the
         *         serial port. 
         */
        virtual std::streamsize xsgetn(char_type* character, 
                                       std::streamsize numberOfBytes) override;

        /**
         * @brief Writes the specified character to the associated serial port.
         * @param character The character to be written to the serial port.
         * @return Returns the character. 
         */
        virtual int_type overflow(const int_type character) override;

        /**
         * @brief Reads and returns the next character from the associated
         *        serial port if one otherwise returns traits::eof(). This
         *        method is used for buffered I/O while uflow() is called
         *        for unbuffered I/O.
         * @return Returns the next character from the serial port.
         */
        virtual int_type underflow() override;

        /**
         * @brief Reads and returns the next character from the associated
         *        serial port if one otherwise returns traits::eof(). This
         *        method is used for unbuffered I/O while underflow() is
         *        called for unbuffered I/O.
         * @return Returns the next character from the serial port.  
         */
        virtual int_type uflow() override;

        /**
         * @brief This function is called when a putback of a character
         *        fails. This must be implemented for unbuffered I/O as all
         *        streambuf subclasses are required to provide putback of
         *        at least one character.
         * @param character The character to putback.
         * @return Returns The character iff successful, otherwise eof to signal an error.
         */
        virtual int_type pbackfail(const int_type character = traits_type::eof()) override;

        /**
         * @brief Checks whether input is available on the port.
         *        If you call \c SerialStream::in_avail, this method will
         *        be called to check for available input.
         *        \code
         *        while(serial_port.rdbuf()->in_avail() > 0)
         *        {
         *            serial_port.get(ch);
         *            ...
         *        }
         *        \endcode
         * @return Returns 1 if characters are available at the serial port,
         *         0 if no characters are available, and -1 if unsuccessful.
         */
        virtual std::streamsize showmanyc() override;

    private:
 
        /**
         * @brief Prevents copying of objects of this class by declaring the copy
         *        constructor private. This method is never defined.
         */
        SerialStreamBuf(const SerialStreamBuf& otherSerialPort) = delete;

        /**
         * @brief Move construction is disallowed.
         */
        SerialStreamBuf(const SerialStreamBuf&& otherSerialPort) = delete;

        /**
         * @brief Prevents copying of objects of this class by declaring the
         *        assignment operator private. This method is never defined.
         */
        SerialStreamBuf& operator=(const SerialStreamBuf& otherSerialPort) = delete;

        /**
         * @brief Move assignment is not allowed.
         */
        SerialStreamBuf& operator=(const SerialStreamBuf&& otherSerialPort) = delete;

        /**
         * @brief Forward declaration of the Implementation class folowing
         *        the PImpl idiom.
         */
        class Implementation;

        /**
         * @brief Pointer to Implementation class instance.
         */
        std::unique_ptr<Implementation> mImpl;

    }; // class SerialStreamBuf

} // namespace LibSerial

#endif // #ifndef _SerialStreamBuf_h_