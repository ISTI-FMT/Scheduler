#pragma once

#using <mscorlib.dll>
#using <System.dll>
#using <System.Xml.dll>

using namespace System::Security::Permissions;
[assembly:SecurityPermissionAttribute(SecurityAction::RequestMinimum, SkipVerification=false)];
// 
// Codice sorgente generato automaticamente da xsd, versione=4.0.30319.17929.
// 
using namespace System::Xml::Serialization;
using namespace System;
ref class orario;
ref class orarioTreno;
ref class orarioTrenoStazione;
ref class orarioTrenoStazioneItinerarioEntrata;
ref class orarioTrenoStazioneItinerarioUscita;


/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"xsd", L"4.0.30319.17929"), 
System::SerializableAttribute, 
System::Diagnostics::DebuggerStepThroughAttribute, 
System::ComponentModel::DesignerCategoryAttribute(L"code"), 
System::Xml::Serialization::XmlTypeAttribute(AnonymousType=true, Namespace=L"urn:tabellaorario-schema"), 
System::Xml::Serialization::XmlRootAttribute(Namespace=L"urn:tabellaorario-schema", IsNullable=false)]
public ref class orario {
    
    private: cli::array< orarioTreno^  >^  trenoField;
    
    /// <remarks/>
    public: [System::Xml::Serialization::XmlElementAttribute(L"treno")]
    property cli::array< orarioTreno^  >^  treno {
        cli::array< orarioTreno^  >^  get();
        System::Void set(cli::array< orarioTreno^  >^  value);
    }
};

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"xsd", L"4.0.30319.17929"), 
System::SerializableAttribute, 
System::Diagnostics::DebuggerStepThroughAttribute, 
System::ComponentModel::DesignerCategoryAttribute(L"code"), 
System::Xml::Serialization::XmlTypeAttribute(AnonymousType=true, Namespace=L"urn:tabellaorario-schema")]
public ref class orarioTreno {
    
    private: cli::array< orarioTrenoStazione^  >^  stazioneField;
    
    private: System::String^  idField;
    
    /// <remarks/>
    public: [System::Xml::Serialization::XmlElementAttribute(L"stazione")]
    property cli::array< orarioTrenoStazione^  >^  stazione {
        cli::array< orarioTrenoStazione^  >^  get();
        System::Void set(cli::array< orarioTrenoStazione^  >^  value);
    }
    
    /// <remarks/>
    public: [System::Xml::Serialization::XmlAttributeAttribute(DataType=L"nonNegativeInteger")]
    property System::String^  id {
        System::String^  get();
        System::Void set(System::String^  value);
    }
};

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"xsd", L"4.0.30319.17929"), 
System::SerializableAttribute, 
System::Diagnostics::DebuggerStepThroughAttribute, 
System::ComponentModel::DesignerCategoryAttribute(L"code"), 
System::Xml::Serialization::XmlTypeAttribute(AnonymousType=true, Namespace=L"urn:tabellaorario-schema")]
public ref class orarioTrenoStazione {
    
    private: System::DateTime arrivoField;
    
    private: System::DateTime partenzaField;
    
    private: System::String^  binarioprogrammatoField;
    
    private: System::String^  latoaperturaporteprogrammatoField;
    
    private: orarioTrenoStazioneItinerarioEntrata^  itinerarioEntrataField;
    
    private: orarioTrenoStazioneItinerarioUscita^  itinerarioUscitaField;
    
    private: System::String^  nameField;
    
    private: System::String^  idField;
    
    /// <remarks/>
    public: [System::Xml::Serialization::XmlElementAttribute(DataType=L"time")]
    property System::DateTime arrivo {
        System::DateTime get();
        System::Void set(System::DateTime value);
    }
    
    /// <remarks/>
    public: [System::Xml::Serialization::XmlElementAttribute(DataType=L"time")]
    property System::DateTime partenza {
        System::DateTime get();
        System::Void set(System::DateTime value);
    }
    
    /// <remarks/>
    public: [System::Xml::Serialization::XmlElementAttribute(DataType=L"nonNegativeInteger")]
    property System::String^  binarioprogrammato {
        System::String^  get();
        System::Void set(System::String^  value);
    }
    
    /// <remarks/>
    public: property System::String^  latoaperturaporteprogrammato {
        System::String^  get();
        System::Void set(System::String^  value);
    }
    
    /// <remarks/>
    public: property orarioTrenoStazioneItinerarioEntrata^  itinerarioEntrata {
        orarioTrenoStazioneItinerarioEntrata^  get();
        System::Void set(orarioTrenoStazioneItinerarioEntrata^  value);
    }
    
    /// <remarks/>
    public: property orarioTrenoStazioneItinerarioUscita^  itinerarioUscita {
        orarioTrenoStazioneItinerarioUscita^  get();
        System::Void set(orarioTrenoStazioneItinerarioUscita^  value);
    }
    
    /// <remarks/>
    public: [System::Xml::Serialization::XmlAttributeAttribute]
    property System::String^  name {
        System::String^  get();
        System::Void set(System::String^  value);
    }
    
    /// <remarks/>
    public: [System::Xml::Serialization::XmlAttributeAttribute(DataType=L"nonNegativeInteger")]
    property System::String^  id {
        System::String^  get();
        System::Void set(System::String^  value);
    }
};

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"xsd", L"4.0.30319.17929"), 
System::SerializableAttribute, 
System::Diagnostics::DebuggerStepThroughAttribute, 
System::ComponentModel::DesignerCategoryAttribute(L"code"), 
System::Xml::Serialization::XmlTypeAttribute(AnonymousType=true, Namespace=L"urn:tabellaorario-schema")]
public ref class orarioTrenoStazioneItinerarioEntrata {
    
    private: System::String^  idField;
    
    private: System::String^  valueField;
    
    /// <remarks/>
    public: [System::Xml::Serialization::XmlAttributeAttribute(DataType=L"nonNegativeInteger")]
    property System::String^  id {
        System::String^  get();
        System::Void set(System::String^  value);
    }
    
    /// <remarks/>
    public: [System::Xml::Serialization::XmlTextAttribute]
    property System::String^  Value {
        System::String^  get();
        System::Void set(System::String^  value);
    }
};

/// <remarks/>
[System::CodeDom::Compiler::GeneratedCodeAttribute(L"xsd", L"4.0.30319.17929"), 
System::SerializableAttribute, 
System::Diagnostics::DebuggerStepThroughAttribute, 
System::ComponentModel::DesignerCategoryAttribute(L"code"), 
System::Xml::Serialization::XmlTypeAttribute(AnonymousType=true, Namespace=L"urn:tabellaorario-schema")]
public ref class orarioTrenoStazioneItinerarioUscita {
    
    private: System::String^  idField;
    
    private: System::String^  valueField;
    
    /// <remarks/>
    public: [System::Xml::Serialization::XmlAttributeAttribute(DataType=L"nonNegativeInteger")]
    property System::String^  id {
        System::String^  get();
        System::Void set(System::String^  value);
    }
    
    /// <remarks/>
    public: [System::Xml::Serialization::XmlTextAttribute]
    property System::String^  Value {
        System::String^  get();
        System::Void set(System::String^  value);
    }
};


inline cli::array< orarioTreno^  >^  orario::treno::get() {
    return this->trenoField;
}
inline System::Void orario::treno::set(cli::array< orarioTreno^  >^  value) {
    this->trenoField = value;
}


inline cli::array< orarioTrenoStazione^  >^  orarioTreno::stazione::get() {
    return this->stazioneField;
}
inline System::Void orarioTreno::stazione::set(cli::array< orarioTrenoStazione^  >^  value) {
    this->stazioneField = value;
}

inline System::String^  orarioTreno::id::get() {
    return this->idField;
}
inline System::Void orarioTreno::id::set(System::String^  value) {
    this->idField = value;
}


inline System::DateTime orarioTrenoStazione::arrivo::get() {
    return this->arrivoField;
}
inline System::Void orarioTrenoStazione::arrivo::set(System::DateTime value) {
    this->arrivoField = value;
}

inline System::DateTime orarioTrenoStazione::partenza::get() {
    return this->partenzaField;
}
inline System::Void orarioTrenoStazione::partenza::set(System::DateTime value) {
    this->partenzaField = value;
}

inline System::String^  orarioTrenoStazione::binarioprogrammato::get() {
    return this->binarioprogrammatoField;
}
inline System::Void orarioTrenoStazione::binarioprogrammato::set(System::String^  value) {
    this->binarioprogrammatoField = value;
}

inline System::String^  orarioTrenoStazione::latoaperturaporteprogrammato::get() {
    return this->latoaperturaporteprogrammatoField;
}
inline System::Void orarioTrenoStazione::latoaperturaporteprogrammato::set(System::String^  value) {
    this->latoaperturaporteprogrammatoField = value;
}

inline orarioTrenoStazioneItinerarioEntrata^  orarioTrenoStazione::itinerarioEntrata::get() {
    return this->itinerarioEntrataField;
}
inline System::Void orarioTrenoStazione::itinerarioEntrata::set(orarioTrenoStazioneItinerarioEntrata^  value) {
    this->itinerarioEntrataField = value;
}

inline orarioTrenoStazioneItinerarioUscita^  orarioTrenoStazione::itinerarioUscita::get() {
    return this->itinerarioUscitaField;
}
inline System::Void orarioTrenoStazione::itinerarioUscita::set(orarioTrenoStazioneItinerarioUscita^  value) {
    this->itinerarioUscitaField = value;
}

inline System::String^  orarioTrenoStazione::name::get() {
    return this->nameField;
}
inline System::Void orarioTrenoStazione::name::set(System::String^  value) {
    this->nameField = value;
}

inline System::String^  orarioTrenoStazione::id::get() {
    return this->idField;
}
inline System::Void orarioTrenoStazione::id::set(System::String^  value) {
    this->idField = value;
}


inline System::String^  orarioTrenoStazioneItinerarioEntrata::id::get() {
    return this->idField;
}
inline System::Void orarioTrenoStazioneItinerarioEntrata::id::set(System::String^  value) {
    this->idField = value;
}

inline System::String^  orarioTrenoStazioneItinerarioEntrata::Value::get() {
    return this->valueField;
}
inline System::Void orarioTrenoStazioneItinerarioEntrata::Value::set(System::String^  value) {
    this->valueField = value;
}


inline System::String^  orarioTrenoStazioneItinerarioUscita::id::get() {
    return this->idField;
}
inline System::Void orarioTrenoStazioneItinerarioUscita::id::set(System::String^  value) {
    this->idField = value;
}

inline System::String^  orarioTrenoStazioneItinerarioUscita::Value::get() {
    return this->valueField;
}
inline System::Void orarioTrenoStazioneItinerarioUscita::Value::set(System::String^  value) {
    this->valueField = value;
}
