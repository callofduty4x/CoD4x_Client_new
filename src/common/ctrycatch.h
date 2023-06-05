/*
 This file is a part of CTryCatch library ( https://github.com/Jamesits/CTryCatch ).
 
 The MIT License (MIT)
 
 Copyright (c) 2016 James Swineson
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#pragma once
#ifndef ctrycatch_h
#define ctrycatch_h

#include <setjmp.h>
#include <stdbool.h>


// Exception types
enum class Exception_type {
    Exception, // Caution: 0 **IS** defined as "no error" to make it work. DO NOT modify this line. 
    AccessViolationException,
    AppDomainUnloadedException,
    ApplicationException,
    ArgumentException,
    ArgumentNullException,
    ArgumentOutOfRangeException,
    ArithmeticException,
    ArrayTypeMismatchException,
    BadImageFormatException,
    CannotUnloadAppDomainException,
    ContextMarshalException,
    DataMisalignedException,
    DivideByZeroException,
    DllNotFoundException,
    DuplicateWaitObjectException,
    EntryPointNotFoundException,
    ExecutionEngineException,
    FieldAccessException,
    FormatException,
    IndexOutOfRangeException,
    InsufficientMemoryException,
    InvalidCastException,
    InvalidOperationException,
    InvalidProgramException,
    MemberAccessException,
    MethodAccessException,
    MissingFieldException,
    MissingMemberException,
    MissingMethodException,
    MulticastNotSupportedException,
    NotFiniteNumberException,
    NotImplementedException,
    NotSupportedException,
    NullReferenceException,
    ObjectDisposedException,
    OperationCanceledException,
    OutOfMemoryException,
    OverflowException,
    PlatformNotSupportedException,
    RankException,
    StackOverflowException,
    SystemException,
    TimeoutException,
    TypeInitializationException,
    TypeLoadException,
    TypeUnloadedException,
    UnauthorizedAccessException,
    KeyNotFoundException,
    DirectoryNotFoundException,
    DriveNotFoundException,
    EndOfStreamException,
    FileLoadException,
    FileNotFoundException,
    IOException,
    PathTooLongException,
    IsolatedStorageException,
    AmbiguousMatchException,
    CustomAttributeFormatException,
    InvalidFilterCriteriaException,
    MetadataException,
    ReflectionTypeLoadException,
    TargetException,
    TargetInvocationException,
    TargetParameterCountException,
    MissingManifestResourceException,
    MissingSatelliteAssemblyException,
    RuntimeWrappedException,
    COMException,
    ExternalException,
    InvalidComObjectException,
    InvalidOleVariantTypeException,
    MarshalDirectiveException,
    SafeArrayRankMismatchException,
    SafeArrayTypeMismatchException,
    SEHException,
    RemotingException,
    RemotingTimeoutException,
    ServerException,
    SerializationException,
    HostProtectionException,
    SecurityException,
    VerificationException,
    XmlSyntaxException,
    PrivilegeNotHeldException,
    CryptographicException,
    CryptographicUnexpectedOperationException,
    PolicyException,
    IdentityNotMappedException,
    DecoderFallbackException,
    EncoderFallbackException,
    AbandonedMutexException,
    SynchronizationLockException,
    ThreadAbortException,
    ThreadInterruptedException,
    ThreadStartException,
    ThreadStateException,
    WaitHandleCannotBeOpenedException,
    ContractPlusAssertionException,
    ContractPlusAssumptionException,
    ContractPlusInvariantException,
    ContractPlusPostconditionException,
    ContractPlusPreconditionException,
    AddInBaseInAddInFolderException,
    AddInSegmentDirectoryNotFoundException,
    InvalidPipelineStoreException,
    GenericsNotImplementedException,
    ConfigurationErrorsException,
    ProviderException,
    InstallException,
    ModuleLoadException,
    ModuleLoadExceptionHandlerException,
    InvalidUdtException,
    ConstraintException,
    DataException,
    DBConcurrencyException,
    DeletedRowInaccessibleException,
    DuplicateNameException,
    EvaluateException,
    InRowChangingEventException,
    InvalidConstraintException,
    InvalidExpressionException,
    MissingPrimaryKeyException,
    NoNullAllowedException,
    OperationAbortedException,
    ReadOnlyException,
    RowNotInTableException,
    StrongTypingException,
    SyntaxErrorException,
    TypedDataSetGeneratorException,
    VersionNotFoundException,
    DbException,
    OdbcException,
    OleDbException,
    SqlException,
    SqlAlreadyFilledException,
    SqlNotFilledException,
    SqlNullValueException,
    SqlTruncateException,
    SqlTypeException,
    InvalidPrinterException,
    DirectoryServicesCOMException,
    ActiveDirectoryObjectExistsException,
    ActiveDirectoryObjectNotFoundException,
    ActiveDirectoryOperationException,
    ActiveDirectoryServerDownException,
    ForestTrustCollisionException,
    SyncFromAllServersOperationException,
    ManagementException,
    MessageQueueException,
    HttpCompileException,
    HttpException,
    HttpParseException,
    HttpRequestValidationException,
    HttpUnhandledException,
    DatabaseNotEnabledForNotificationException,
    TableNotEnabledForNotificationException,
    HostingEnvironmentException,
    SqlExecutionException,
    MembershipCreateUserException,
    MembershipPasswordException,
    ViewStateException,
    AxHostPlusInvalidActiveXStateException,
    CodeDomSerializerException,
    DataSourceGeneratorException,
    DataSourceSerializationException,
    InternalException,
    NameValidationException,
    XmlException,
    UpaException,
    XmlSchemaException,
    XmlSchemaInferenceException,
    XmlSchemaValidationException,
    XPathException,
    XsltCompileException,
    XsltException,
    UriFormatException,
    InvalidAsynchronousStateException,
    InvalidEnumArgumentException,
    LicenseException,
    WarningException,
    Win32Exception,
    CheckoutException,
    ConfigurationException,
    SettingsPropertyIsReadOnlyException,
    SettingsPropertyNotFoundException,
    SettingsPropertyWrongTypeException,
    InternalBufferOverflowException,
    InvalidDataException,
    CookieException,
    HttpListenerException,
    ProtocolViolationException,
    WebException,
    SmtpException,
    SmtpFailedRecipientException,
    SmtpFailedRecipientsException,
    NetworkInformationException,
    PingException,
    SocketException,
    AuthenticationException,
    InvalidCredentialException,
    SemaphoreFullException
};

struct exception_try_record_t
{
    exception_try_record_t* next;
    Exception_type type;
    jmp_buf context;
};

exception_try_record_t* CTryCatch_AddNewHandler(exception_try_record_t*);
void CTryCatch_RemoveTopHandler();
void CTryCatch_Throw(Exception_type exception, const char* exceptionmsg);



// Some macro magic
#define CONCAT_(x,y) x##y
#define CONCAT(x,y) CONCAT_(x,y)
#define uniquename CONCAT(VAR_NAME_, __LINE__)

#define CTRYCATCH_PRIMITIVE_CAT(a, b, ...) a ## b ## __VA_ARGS__
#define CTRYCATCH_CAT(a, b, ...) CTRYCATCH_PRIMITIVE_CAT(a, b, __VA_ARGS__)
#define CTRYCATCH_NAME(X) CTRYCATCH_CAT(__ctrycatch_, X, __LINE__)

// New block arguments
#define TRY(X) \
            struct exception_try_record_t CTRYCATCH_NAME(exception_env_); \
            CTRYCATCH_NAME(exception_env_).type = X;\
            CTRYCATCH_NAME(exception_env_).next = CTryCatch_AddNewHandler(&CTRYCATCH_NAME(exception_env_));\
    if(!setjmp(CTRYCATCH_NAME(exception_env_).context))

#define CATCH \
    else

#define ENDTRY \
            CTryCatch_RemoveTopHandler();

//#define THROW(X,...) 
//    CTRYCATCH_NAME(exception_message) = (__VA_ARGS__  +0), longjmp(CTRYCATCH_NAME(exception_env), (X))

#define THROW(X) \
    CTryCatch_Throw(X, "")

#endif /* ctrycatch_h */